﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TW_BaseCharacter.generated.h"


class ATW_Gun;
class UStaticMeshComponent;
class UAnimMontage;
class UNiagaraComponent;
class UAnimInstance;
class UDecalComponent;

UCLASS()
class TW_API ATW_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATW_BaseCharacter();

	bool FireGun();
	
	bool CheckIsAiming() const { return bIsAiming;}

	void SetTagVisibility(bool Visibility, FRotator ShotDirection = FRotator::ZeroRotator, float TagHeight = 0.f);

	bool IsTagged() const {return bTaggedVisible;}
	
protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ReloadGun(float ReloadTime);

	UFUNCTION()
	void FinishedReloading();
	
	UPROPERTY(EditAnywhere, Category = Gun)
	TSubclassOf<ATW_Gun> GunClass;

	UPROPERTY()
	ATW_Gun* Gun = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
	int32 MaxAmmo = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 CurrentHealth = 0;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	UNiagaraComponent* BloodImpact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hat")
	UStaticMeshComponent* HatMesh;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* FireGunMontage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* ReloadGunMontage;

	UPROPERTY(EditAnywhere, Category = "DeadEyeMarker")
	UStaticMeshComponent* DeadEyeMarkerMesh;

	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	bool bReloadingGun = false;

	bool bIsAiming = false;

	bool bTaggedVisible = false;
	
	FTimerHandle ReloadTimer;
};
