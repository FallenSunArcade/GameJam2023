// Copyright Epic Games, Inc. All Rights Reserved.

#include "TW_Characters/TW_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TW_Actors/TW_Gun.h"
#include "TW_UI/TW_Hud.h"


ATW_Player::ATW_Player()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f); // ...at this rotation rate
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
}

void ATW_Player::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		Hud = Cast<ATW_Hud>(PlayerController->GetHUD());
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	GunFired.AddDynamic(this, &ATW_Player::GunWasFired);
	PlayerDamaged.AddDynamic(this, &ATW_Player::PlayerWasDamaged);
	StartDeadEye.AddDynamic(this, &ATW_Player::DeadEyeInProgress);
	EndDeadEye.AddDynamic(this, &ATW_Player::DeadEyeEnded);
	PlayerAiming.AddDynamic(this, &ATW_Player::IsPlayerAiming);
	
	GetWorldTimerManager().SetTimer(UpdateDeadEyeMeterHandle, this, &ATW_Player::UpdateDeadEyeMeter, 1.f, true, 0.f);
}

float ATW_Player::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Display, TEXT("Taking Damage %d (%s)"), CurrentHealth, *GetName());
	PlayerDamaged.Broadcast(CurrentHealth);

	return DamageTaken;
}

void ATW_Player::FillAmmo()
{
	Super::FillAmmo();
	GunFired.Broadcast(Gun->GetCurrentAmmo(), Gun->GetTotalAmmo());
}

void ATW_Player::UpdateDeadEyeMeter()
{
	if(bDeadEyeInProgress)
	{
		--CurrentDeadEyeTime;
		CurrentDeadEyeTime = FMath::Clamp(CurrentDeadEyeTime, 0, MaxDeadEyeTime);
		if(CurrentDeadEyeTime > 0)
		{
			StartDeadEye.Broadcast(CurrentDeadEyeTime);
		}
		else
		{
			if(Hud)
			{
				Hud->SetDeadEye(false);
			}		

			GetWorldTimerManager().SetTimer(UpdateDeadEyeMeterHandle, this, &ATW_Player::UpdateDeadEyeMeter, 1.f, true, 1.f);
			EndDeadEye.Broadcast(CurrentDeadEyeTime);
			bDeadEyeInProgress = false;
		}
	}
	else
	{
		++CurrentDeadEyeTime;
		CurrentDeadEyeTime = FMath::Clamp(CurrentDeadEyeTime, 0, MaxDeadEyeTime);
		EndDeadEye.Broadcast(CurrentDeadEyeTime);
	}
}

void ATW_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATW_Player::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATW_Player::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATW_Player::Shoot);
		EnhancedInputComponent->BindAction(StartAimAction, ETriggerEvent::Triggered, this, &ATW_Player::StartAiming);
		EnhancedInputComponent->BindAction(StopAimAction, ETriggerEvent::Triggered, this, &ATW_Player::StopAiming);
		EnhancedInputComponent->BindAction(DeadEyeAction, ETriggerEvent::Triggered, this, &ATW_Player::DeadEye);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ATW_Player::Reload);
	}
}

void ATW_Player::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATW_Player::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * GetWorld()->GetDeltaSeconds() * TurnRate);
		AddControllerPitchInput(LookAxisVector.Y* GetWorld()->GetDeltaSeconds() * TurnRate);
	}
}

void ATW_Player::Shoot(const FInputActionValue& Value)
{
	if(FireGun())
	{
		GunFired.Broadcast(CurrentAmmo, Gun->GetTotalAmmo());
		
		if(ShootingCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ShootingCameraShakeClass);
		}
	}
}

void ATW_Player::StartAiming(const FInputActionValue& Value)
{
	PlayerAiming.Broadcast(true);
	bIsAiming = true;
	CameraBoom->TargetArmLength = 150;
}

void ATW_Player::StopAiming(const FInputActionValue& Value)
{
	PlayerAiming.Broadcast(false);
	bIsAiming = false;
	CameraBoom->TargetArmLength = 250;
}

void ATW_Player::DeadEye(const FInputActionValue& Value)
{
	if(!bDeadEyeInProgress)
	{
		if(Hud)
		{
			Hud->SetDeadEye(true);
		}
		
		bDeadEyeInProgress = true;
		StartDeadEye.Broadcast(CurrentDeadEyeTime);
		GetWorldTimerManager().SetTimer(UpdateDeadEyeMeterHandle, this, &ATW_Player::UpdateDeadEyeMeter, 0.1f, true, 0.f);
	}
	else
	{
		if(Hud)
		{
			Hud->SetDeadEye(false);
		}
		
		GetWorldTimerManager().SetTimer(UpdateDeadEyeMeterHandle, this, &ATW_Player::UpdateDeadEyeMeter, 1.f, true, 1.f);
		bDeadEyeInProgress = false;
		EndDeadEye.Broadcast(CurrentDeadEyeTime);
	}
}

void ATW_Player::Reload(const FInputActionValue& Value)
{
	ReloadGun();
}





