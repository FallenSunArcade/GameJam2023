// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TW_GameMode.generated.h"

struct FWave
{
	int32 Grunts;
	int32 Bosses;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStatusDelegate, const FString&, GameStatus);

class ATW_SpawnPoint;

UCLASS()
class TW_API ATW_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATW_GameMode();
	void AddGruntSpawnPoint(ATW_SpawnPoint* SpawnPoint);
	void AddBossSpawnPoint(ATW_SpawnPoint* SpawnPoint);
	void UnitDied();

	UPROPERTY(BlueprintAssignable)
	FGameStatusDelegate GameStatusDelegate;
	
protected:
	virtual void BeginPlay() override;
	void StartWave();
	
private:
	TArray<ATW_SpawnPoint*> GruntSpawnPoints;
	
	TArray<ATW_SpawnPoint*> BossSpawnPoints;
	
	FTimerHandle StartWaveHandle;

	TQueue<FWave> Waves;

	int32 RemainingUnits = 0;

	int32 CurrentWaveNumber = 1;
};
