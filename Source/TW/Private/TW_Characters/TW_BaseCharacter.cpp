﻿// Fill out your copyright notice in the Description page of Project Settings.


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

	DeadEyeMarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Dead Eye Marker");
	DeadEyeMarkerMesh->SetupAttachment(GetRootComponent());
	SetTagVisibility(false);
}

bool ATW_BaseCharacter::FireGun()
{
	
	if(CurrentAmmo > 0 && !bIsReloading)
	{
		if(Gun && AnimInstance && !bIsShooting)
		{
			if(bIsAiming)
			{
				AnimInstance->Montage_Play(FireGunAimMontage);
			}
			else
			{
				AnimInstance->Montage_Play(FireGunHipMontage);
			}
			
			Gun->FireGun();
			CurrentAmmo = Gun->GetCurrentAmmo();
		}
		return true;
	}
	else
	{
		ReloadGun();
	}

	return false;
}

void ATW_BaseCharacter::SetTagVisibility(bool Visibility, FRotator ShotDirection, float TagHeight)
{
	bTaggedVisible = Visibility;
	FVector TagLocation = DeadEyeMarkerMesh->GetComponentLocation();
	TagLocation.Z = TagHeight;
	DeadEyeMarkerMesh->SetWorldRotation(ShotDirection);
	DeadEyeMarkerMesh->SetWorldLocation(TagLocation);
	DeadEyeMarkerMesh->SetVisibility(Visibility);
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
			Gun->InitializeGun();
			CurrentAmmo = Gun->GetAmmoLoadingCapacity();
			MaxAmmo = Gun->GetTotalAmmo();
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

void ATW_BaseCharacter::ReloadGun()
{
	if(!bIsReloading && Gun->GetTotalAmmo() != 0 && CurrentAmmo != Gun->GetLoadingCapacity())
	{
		Gun->RefillAmmo();
		if(AnimInstance)
		{
			AnimInstance->Montage_Play(ReloadGunMontage);
		}
	}
}

void ATW_BaseCharacter::FillAmmo()
{
	CurrentAmmo = Gun->GetCurrentAmmo();
}

