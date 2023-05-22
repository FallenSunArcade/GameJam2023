// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Characters/TW_BaseCharacter.h"
#include "TW_Actors/TW_Gun.h"
#include "Components/CapsuleComponent.h"

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
		if(Gun)
		{
			Gun->FireGun();
		}
		--CurrentAmmo;
		return true;
	}

	return false;
}

void ATW_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(*GunClass)
	{
		if(Gun = GetWorld()->SpawnActor<ATW_Gun>(GunClass))
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			Gun->SetOwner(this);
			Gun->InitializeGun();
		}
	}
}

float ATW_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= DamageTaken;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	return DamageTaken;
}

