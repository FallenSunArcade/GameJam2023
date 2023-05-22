// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Gun.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "NiagaraComponent.h"


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

	FVector Location;
	FRotator Rotation;
	FVector ShotDirection;
	GunOwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * 10000;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FHitResult Hit;

	if(GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
	{
		DrawDebugSphere(GetWorld(), Hit.Location, 20, 16, FColor::Red, false, 2.0);
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GunOwnerController, this);
		}

	}
	
}

void ATW_Gun::InitializeGun()
{
	GunOwner = Cast<APawn>(GetOwner());
	check(GunOwner);
	GunOwnerController = GunOwner->GetController();
	check(GunOwnerController);
}

void ATW_Gun::BeginPlay()
{
	Super::BeginPlay();
}


