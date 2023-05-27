// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Gun.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "NiagaraComponent.h"
#include "TW_Actors/TW_Projectile.h"


ATW_Gun::ATW_Gun()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
	MuzzleFlash = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash"));
	MuzzleFlash->SetupAttachment(GunMesh);
}

void ATW_Gun::RefillAmmo()
{
	if(bInfiniteAmmo)
	{
		CurrentAmmo = AmmoLoadingCapacity;
	}
	else
	{
		if(TotalAmmo < AmmoLoadingCapacity)
		{
			CurrentAmmo = TotalAmmo;
			TotalAmmo = 0;
		}
		else
		{
			CurrentAmmo = AmmoLoadingCapacity;
			TotalAmmo -= AmmoLoadingCapacity;
		}
	}
}

void ATW_Gun::FireGun(FVector ManualLocation, FRotator ManualRotation, bool ManualFireGun)
{
	--CurrentAmmo;
	CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, AmmoLoadingCapacity);
	
	GetWorldTimerManager().SetTimer(MuzzleFlashTimer, this, &ATW_Gun::StopMuzzleFlash, 0.2f, false);
	MuzzleFlash->Activate(true);

	UGameplayStatics::PlaySoundAtLocation(this, GunShootingSound, GetActorLocation());


	FVector Location;
	FRotator Rotation;
	
	if(ManualFireGun)
	{
		if(const AActor* ThisGunsOwner = GetOwner())
		{
			Location = ThisGunsOwner->GetActorLocation();
			Rotation = (ManualLocation - Location).Rotation();
		}
	}
	else
	{
		GunOwnerController->GetPlayerViewPoint(Location, Rotation);
	}
	
	GetWorld()->SpawnActor<ATW_Projectile>(ProjectileClass, Location + Rotation.Vector() * 200,
		Rotation);
}

void ATW_Gun::LoadingGun()
{
	GunOwner = Cast<APawn>(GetOwner());
	GunOwnerController = GunOwner->GetController();
		
	if(GunOwner && GunOwnerController)
	{
		GetWorldTimerManager().ClearTimer(LoadGunTimer);
	}
}

void ATW_Gun::StopMuzzleFlash()
{
	MuzzleFlash->Deactivate();
}

void ATW_Gun::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(LoadGunTimer, this, &ATW_Gun::LoadingGun, 0.1f, true);
}


