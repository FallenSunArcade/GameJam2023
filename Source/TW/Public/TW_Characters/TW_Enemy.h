// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TW_BaseCharacter.h"
#include "TW_Enemy.generated.h"

UCLASS()
class TW_API ATW_Enemy : public ATW_BaseCharacter
{
	GENERATED_BODY()

public:
	ATW_Enemy();
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
};
