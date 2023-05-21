// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Gun.h"
#include "Kismet/GameplayStatics.h"


ATW_Gun::ATW_Gun()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);
}

void ATW_Gun::FireGun()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	if(CurrentAmmo > 0)
	{
		--CurrentAmmo;
	}
}

void ATW_Gun::BeginPlay()
{
	Super::BeginPlay();
	
}


