// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TW_Gun.generated.h"

class UStaticMeshComponent;
class APawn;
class AController;
class UNiagaraComponent;
class USoundBase;
class ATW_Projectile;
class ATW_BaseCharacter;

UCLASS()
class TW_API ATW_Gun : public AActor
{
	GENERATED_BODY()

public:
	ATW_Gun();

	FORCEINLINE int32 GetAmmoLoadingCapacity() const {return AmmoLoadingCapacity;}

	FORCEINLINE int32 GetTotalAmmo() const {return TotalAmmo;}
	
	FORCEINLINE int32 GetCurrentAmmo() const {return CurrentAmmo;}

	FORCEINLINE int32 GetLoadingCapacity() const {return AmmoLoadingCapacity;}
	

	void RefillAmmo();
	
	void FireGun(FVector ManualLocation = FVector::Zero(), FRotator ManualRotation = FRotator::ZeroRotator,
		bool ManualFireGun = false, float ScaleDamage = 1.f);
	
	void LoadingGun();

	UFUNCTION()
	void StopMuzzleFlash();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Gun")
	UStaticMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Gun")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Gun")
	UNiagaraComponent* MuzzleFlash;
	
	UPROPERTY(EditAnywhere, Category = "Gun")
	USoundBase* GunShootingSound;
	
	UPROPERTY(EditAnywhere, Category = "Gun")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	TSubclassOf<ATW_Projectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 TotalAmmo = 150;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 AmmoLoadingCapacity = 6;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 CurrentAmmo = 6;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	bool bInfiniteAmmo = false;

	UPROPERTY()
	ATW_BaseCharacter* GunOwner;

	UPROPERTY()
	AController* GunOwnerController;
	
	FTimerHandle MuzzleFlashTimer;

	FTimerHandle LoadGunTimer;
};
