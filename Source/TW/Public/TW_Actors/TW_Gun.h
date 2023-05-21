// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TW_Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReloadDelegate, int32, CurrentAmmo);

class UStaticMeshComponent;
class APawn;
class AController;

UCLASS()
class TW_API ATW_Gun : public AActor
{
	GENERATED_BODY()

public:
	ATW_Gun();

	FORCEINLINE int32 GetCurrentAmmo() const {return CurrentAmmo;}
	
	FORCEINLINE void SetCurrentAmmo(int32 NewAmmo) {CurrentAmmo = NewAmmo;};
	
	void FireGun();

	void InitializeGun();
	
	UPROPERTY()
	FReloadDelegate ReloadGun;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Gun")
	UStaticMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Gun")
	UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo;
	
	UPROPERTY(EditAnywhere)
	float Damage = 10;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 CurrentAmmo;

	UPROPERTY()
	APawn* GunOwner;

	UPROPERTY()
	AController* GunOwnerController;
};
