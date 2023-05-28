// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Characters/TW_Enemy.h"
#include "TW_GameModes/TW_GameMode.h"
#include "Kismet/GameplayStatics.h"

ATW_Enemy::ATW_Enemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATW_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATW_Enemy::Destroyed()
{
	Super::Destroyed();

	if(ATW_GameMode* GameMode = Cast<ATW_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->UnitDied();
	}
}


