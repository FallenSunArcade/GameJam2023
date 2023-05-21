// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Characters/TW_BaseCharacter.h"
#include "TW_Actors/TW_Gun.h"

ATW_BaseCharacter::ATW_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
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
		}
	}
}

float ATW_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

