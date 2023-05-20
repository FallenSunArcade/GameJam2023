// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Controllers/TW_PlayerController.h"


// Sets default values
ATW_PlayerController::ATW_PlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATW_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATW_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

