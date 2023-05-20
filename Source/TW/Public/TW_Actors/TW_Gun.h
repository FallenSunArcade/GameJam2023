// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TW_Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGunFiredDelegate, int32, CurrentAmmo);

UCLASS()
class TW_API ATW_Gun : public AActor
{
	GENERATED_BODY()

public:
	ATW_Gun();

	UFUNCTION()
	void FireGun();
	
	UPROPERTY()
	FGunFiredDelegate GunFired;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 CurrentAmmo;
};
