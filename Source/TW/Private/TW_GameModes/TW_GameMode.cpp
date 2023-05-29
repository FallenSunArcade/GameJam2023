// Fill out your copyright notice in the Description page of Project Settings.


#include "TW/Public/TW_GameModes/TW_GameMode.h"
#include "TW_Actors/TW_SpawnPoint.h"


ATW_GameMode::ATW_GameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	Waves.Enqueue({5, 0});
	Waves.Enqueue({10, 0});
	Waves.Enqueue({10, 1});
}

void ATW_GameMode::AddGruntSpawnPoint(ATW_SpawnPoint* SpawnPoint)
{
	GruntSpawnPoints.Emplace(SpawnPoint);
}

void ATW_GameMode::AddBossSpawnPoint(ATW_SpawnPoint* SpawnPoint)
{
	BossSpawnPoints.Emplace(SpawnPoint);
}

void ATW_GameMode::UnitDied()
{
	--RemainingUnits;
	if(RemainingUnits == 0)
	{
		++CurrentWaveNumber;
		GameStatusDelegate.Broadcast("Wave Over");
		GetWorldTimerManager().SetTimer(StartWaveHandle, this, &ATW_GameMode::StartWave, 2.f);
	}
}

void ATW_GameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(StartWaveHandle, this, &ATW_GameMode::StartWave, 2.f);
}

void ATW_GameMode::StartWave()
{
	FWave CurrentWave;

	GameStatusDelegate.Broadcast("Wave " + FString::FromInt(CurrentWaveNumber));
	
	if(Waves.Dequeue(CurrentWave))
	{
		RemainingUnits = CurrentWave.Grunts + CurrentWave.Bosses;
		
		for(int i = 0; i < CurrentWave.Grunts; ++i)
		{
			const int32 RandomSpawnPoint = FMath::RandRange(0, GruntSpawnPoints.Num() - 1);
			GruntSpawnPoints[RandomSpawnPoint]->Spawn(false);
		}

		for(int i = 0; i < CurrentWave.Bosses; ++i)
		{
			const int32 RandomSpawnPoint = FMath::RandRange(0, BossSpawnPoints.Num() - 1);
			BossSpawnPoints[RandomSpawnPoint]->Spawn(false);
		}
	}
	else
	{
		GameStatusDelegate.Broadcast("Game Won");
	}
}


