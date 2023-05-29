// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Actors/TW_SpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "TW_Characters/TW_BaseCharacter.h"
#include "TW_GameModes/TW_GameMode.h"

ATW_SpawnPoint::ATW_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATW_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	if(ATW_GameMode* GameMode = Cast<ATW_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(SpawnType == ESpawnTypes::Grunt)
		{
			GameMode->AddGruntSpawnPoint(this);
		}
		else
		{
			GameMode->AddBossSpawnPoint(this);
		}
	}
	
}

void ATW_SpawnPoint::DelayedSpawn()
{
	if(*BaseCharacterClass)
	{
		GetWorld()->SpawnActor<ATW_BaseCharacter>(BaseCharacterClass, GetActorTransform());
	}
}

void ATW_SpawnPoint::Spawn(bool UsingDelay, float Delay)
{
	if(UsingDelay)
	{
		GetWorldTimerManager().SetTimer(SpawnDelay, this, &ATW_SpawnPoint::DelayedSpawn, Delay);
	}
	else
	{
		if(*BaseCharacterClass)
		{
			GetWorld()->SpawnActor<ATW_BaseCharacter>(BaseCharacterClass, GetActorTransform());
		}
	}
}


