// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Gun.h"


ATW_Gun::ATW_Gun()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATW_Gun::FireGun()
{
	if(CurrentAmmo > 0)
	{
		--CurrentAmmo;
	}

	// Update the listeners ammo
	GunFired.Broadcast(CurrentAmmo);
}

void ATW_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}


