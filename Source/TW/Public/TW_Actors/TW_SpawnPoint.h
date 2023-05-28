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
	void Spawn();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	TSubclassOf<ATW_BaseCharacter> BaseCharacterClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	ESpawnTypes SpawnType;
};
