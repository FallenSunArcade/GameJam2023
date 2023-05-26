// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TW_BaseCharacter.generated.h"


class ATW_Gun;
class UStaticMeshComponent;
class UAnimMontage;
class UNiagaraComponent;
class UAnimInstance;
class USoundBase;

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

	void SetShootingFlag(bool ShootingFlag);

	void SetReloadingFlag(bool ReloadingFlag) { bIsReloading = ReloadingFlag; }

	virtual void FillAmmo();
	
protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void ReloadGun();

	UPROPERTY(EditAnywhere, Category = Gun)
	TSubclassOf<ATW_Gun> GunClass;

	UPROPERTY()
	ATW_Gun* Gun = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
	int32 TotalAmmo = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 CurrentHealth = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hat")
	UStaticMeshComponent* HatMesh;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* FireGunHipMontage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* FireGunAimMontage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* ReloadGunMontage;

	UPROPERTY(EditAnywhere, Category = "DeadEyeMarker")
	UStaticMeshComponent* DeadEyeMarkerMesh;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	bool bIsShooting = false;
	
	bool bIsReloading = false;

	bool bIsAiming = false;

	bool bTaggedVisible = false;
};
