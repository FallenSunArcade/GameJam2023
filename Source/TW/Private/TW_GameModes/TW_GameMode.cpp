// Fill out your copyright notice in the Description page of Project Settings.


#include "TW/Public/TW_GameModes/TW_GameMode.h"
#include "TW_Actors/TW_SpawnPoint.h"


ATW_GameMode::ATW_GameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATW_GameMode::AddGruntSpawnPoint(ATW_SpawnPoint* SpawnPoint)
{
	GruntSpawnPoints.Emplace(SpawnPoint);
}

void ATW_GameMode::AddBossSpawnPoint(ATW_SpawnPoint* SpawnPoint)
{
	BossSpawnPoints.Emplace(SpawnPoint);
}

void ATW_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(StartWaveHandle, this, &ATW_GameMode::StartWave, 2.f);
}

void ATW_GameMode::StartWave()
{
	for(const auto GruntSpawn : GruntSpawnPoints)
	{
		GruntSpawn->Spawn();
	}
}


