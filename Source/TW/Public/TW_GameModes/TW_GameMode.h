// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TW_GameMode.generated.h"

class ATW_SpawnPoint;

UCLASS()
class TW_API ATW_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATW_GameMode();
	void AddGruntSpawnPoint(ATW_SpawnPoint* SpawnPoint);
	void AddBossSpawnPoint(ATW_SpawnPoint* SpawnPoint);

protected:
	virtual void BeginPlay() override;
	void StartWave();
	
private:
	TArray<ATW_SpawnPoint*> GruntSpawnPoints;
	TArray<ATW_SpawnPoint*> BossSpawnPoints;
	FTimerHandle StartWaveHandle;
};
