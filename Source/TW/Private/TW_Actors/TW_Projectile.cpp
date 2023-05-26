// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_Projectile.h"


// Sets default values
ATW_Projectile::ATW_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATW_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATW_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

