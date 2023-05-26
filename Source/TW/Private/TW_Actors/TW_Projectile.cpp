// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
ATW_Projectile::ATW_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UBoxComponent>(TEXT("Projectile"));
	SetRootComponent(Projectile);

	SmokeTrail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(Projectile);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	
}

void ATW_Projectile::BeginPlay()
{
	Super::BeginPlay();
	Projectile->OnComponentHit.AddDynamic(this, &ATW_Projectile::OnHit);
}

void ATW_Projectile::Destroyed()
{
	Super::Destroyed();
}

void ATW_Projectile::StartDestroyTimer()
{
	GetWorldTimerManager().SetTimer(
	DestroyTimer,
	this,
	&ATW_Projectile::DestroyTimerFinished,
	1.f
);
}

void ATW_Projectile::DestroyTimerFinished()
{
	Destroy();
}

void ATW_Projectile::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                           FVector NormalImpulse, const FHitResult& Hit)
{
	StartDestroyTimer();

	if (AActor* HitActor = Hit.GetActor())
	{
		FPointDamageEvent DamageEvent(Damage, Hit, NormalImpulse, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, nullptr, this);
	}
}


