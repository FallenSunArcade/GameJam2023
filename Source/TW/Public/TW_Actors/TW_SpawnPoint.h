// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TW_SpawnPoint.generated.h"

UENUM(BlueprintType)
enum class ESpawnTypes : uint8 {
	Grunt       UMETA(DisplayName="Grunt"),
	Boss        UMETA(DisplayName="Boss") 
};

class ATW_BaseCharacter;

UCLASS()
class TW_API ATW_SpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ATW_SpawnPoint();
	void Spawn(bool UsingDelay, float Delay = 0.f);
	
protected:
	virtual void BeginPlay() override;
	void DelayedSpawn();
private:
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	TSubclassOf<ATW_BaseCharacter> BaseCharacterClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	ESpawnTypes SpawnType;

	FTimerHandle SpawnDelay;
};
