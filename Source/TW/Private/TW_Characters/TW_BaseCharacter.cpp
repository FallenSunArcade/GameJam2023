// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Characters/TW_BaseCharacter.h"
#include "TW_Actors/TW_Gun.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Engine/DamageEvents.h"

ATW_BaseCharacter::ATW_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(GetCapsuleComponent());

	HatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh"));

	HatMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HatSocket"));
}

bool ATW_BaseCharacter::FireGun()
{
	
	if(CurrentAmmo > 0)
	{
		if(Gun && AnimInstance && FireGunMontage)
		{
			if(bIsAiming)
			{
				AnimInstance->Montage_Stop(0.f, AimGunMontage);
			}
			
			AnimInstance->Montage_Play(FireGunMontage);
			
			if(bIsAiming)
			{
				AnimInstance->Montage_Play(AimGunMontage, 1,  EMontagePlayReturnType::MontageLength,
					AimGunMontage->GetPlayLength(), false);
			}
			
			Gun->FireGun();
			CurrentAmmo = Gun->GetCurrentAmmo();


		}
		return true;
	}

	return false;
}

void ATW_BaseCharacter::StartAimingGunMontage()
{
	if(AnimInstance)
	{
		AnimInstance->Montage_Play(AimGunMontage);
		bIsAiming = true;
	}
}

void ATW_BaseCharacter::StopAimingGunMontage()
{
	if(AnimInstance)
	{
		AnimInstance->Montage_Stop(0.f, AimGunMontage);
		bIsAiming = false;
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
			Gun->InitializeGun();
			CurrentAmmo = Gun->GetAmmoLoadingCapacity();
			MaxAmmo = Gun->GetTotalAmmo();
			Gun->ReloadGun.AddDynamic(this, &ATW_BaseCharacter::ReloadGun);
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();
}

float ATW_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= DamageTaken;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	return DamageTaken;
}

void ATW_BaseCharacter::ReloadGun(float ReloadTime)
{
	if(!bReloadingGun && Gun->GetTotalAmmo() != 0)
	{
		Gun->RefillAmmo();
		if(AnimInstance)
		{
			if(bIsAiming)
			{
				AnimInstance->Montage_Stop(0.f, AimGunMontage);
			}
			
			AnimInstance->Montage_Play(ReloadGunMontage);

			if(bIsAiming)
			{
				AnimInstance->Montage_Play(AimGunMontage, 1,  EMontagePlayReturnType::MontageLength,
					ReloadGunMontage->GetPlayLength(), false);
			}
			
			GetWorldTimerManager().SetTimer(ReloadTimer, this, &ATW_BaseCharacter::FinishedReloading, ReloadTime, false);
			bReloadingGun = true;
		}
	}
}

void ATW_BaseCharacter::FinishedReloading()
{
	bReloadingGun = false;
	CurrentAmmo = Gun->GetCurrentAmmo();
}

