// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Characters/TW_BaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "TW_Actors/TW_Gun.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TW_ToolBox/TW_LogCategories.h"

ATW_BaseCharacter::ATW_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(GetCapsuleComponent());

	HatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh"));

	HatMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HatSocket"));

	DeadEyeMarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Dead Eye Marker");
	DeadEyeMarkerMesh->SetupAttachment(GetRootComponent());
	SetTagVisibility(false);
}

bool ATW_BaseCharacter::FireGun(FVector ManualLocation, FRotator ManualRotation, bool ManualFireGun, float ScaleDamage)
{
	
	if(CurrentAmmo > 0 && !bIsReloading && Gun && AnimInstance && !bIsShooting)
	{
		if(bIsAiming)
		{
			AnimInstance->Montage_Play(FireGunAimMontage);
		}
		else
		{
			AnimInstance->Montage_Play(FireGunHipMontage);
		}
			
		Gun->FireGun(ManualLocation, ManualRotation, ManualFireGun, ScaleDamage);
		CurrentAmmo = Gun->GetCurrentAmmo();
		
		return true;
	}
	return false;
}

void ATW_BaseCharacter::SetTagVisibility(bool Visibility, FRotator ShotDirection, float TagHeight)
{
	bTaggedVisible = Visibility;
	UE_LOG(LogDeadeye, Display, TEXT("(SetTagVisibility %s %s)"), (Visibility ? TEXT("true") : TEXT("false")), *GetName());

	FVector TagLocation = DeadEyeMarkerMesh->GetComponentLocation();
	TagLocation.Z = TagHeight;
	DeadEyeMarkerMesh->SetWorldRotation(ShotDirection);
	DeadEyeMarkerMesh->SetWorldLocation(TagLocation);
	DeadEyeMarkerMesh->SetVisibility(Visibility);
}

FVector ATW_BaseCharacter::GetTagLocation()
{
	return DeadEyeMarkerMesh->GetComponentLocation();
}

FRotator ATW_BaseCharacter::GetTagRotation()
{
	return DeadEyeMarkerMesh->GetComponentRotation();
}

void ATW_BaseCharacter::SetShootingFlag(bool ShootingFlag)
{
	bIsShooting = ShootingFlag;

	if(CurrentAmmo == 0)
	{
		ReloadGun();
	}
}

void ATW_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(*GunClass)
	{
		Gun = GetWorld()->SpawnActor<ATW_Gun>(GunClass);
		if(Gun)
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			Gun->SetOwner(this);
			CurrentAmmo = Gun->GetAmmoLoadingCapacity();
			TotalAmmo = Gun->GetTotalAmmo();
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();

	OnDeathDelegate.AddDynamic(this, &ATW_BaseCharacter::OnDeath);
}

float ATW_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= DamageTaken;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if(BloodSplat)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BloodSplat, DamageCauser->GetActorLocation(), DamageCauser->GetActorRotation());
	}

	if(GruntSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GruntSound, GetActorLocation());
	}

	if(BulletHitNoiseSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BulletHitNoiseSound, GetActorLocation());
	}

	if(AnimInstance)
	{
		AnimInstance->Montage_Play(HitImpactMontage);
	}

	if(CurrentHealth == 0)
	{
		OnDeathDelegate.Broadcast();
		
		GetMesh()->SetSimulatePhysics(true);
		GetCharacterMovement()->DisableMovement();
		
		GetWorldTimerManager().SetTimer(
			DeathTimer,
			this,
			&ATW_BaseCharacter::DestroyCharacter,
			1.f
			);
	}

	
	return DamageTaken;
}

void ATW_BaseCharacter::ChangeHealth(int32 HealthValue)
{
	CurrentHealth += HealthValue;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void ATW_BaseCharacter::ChangeAmmo(int32 AmmoValue)
{
	TotalAmmo += AmmoValue;
}

void ATW_BaseCharacter::ReloadGun()
{
	if(!bIsReloading && Gun->GetTotalAmmo() != 0 && CurrentAmmo != Gun->GetLoadingCapacity())
	{
		bIsReloading = true;
		Gun->RefillAmmo();
		if(AnimInstance)
		{
			AnimInstance->Montage_Play(ReloadGunMontage);
		}
	}
}

void ATW_BaseCharacter::DestroyCharacter()
{
	Gun->Destroy();
	Destroy();
}

void ATW_BaseCharacter::FillAmmo()
{
	CurrentAmmo = Gun->GetCurrentAmmo();
	TotalAmmo = Gun->GetTotalAmmo();
}

