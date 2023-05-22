// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TW_BaseCharacter.generated.h"


class ATW_Gun;
class UStaticMeshComponent;
class UAnimMontage;

UCLASS()
class TW_API ATW_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATW_BaseCharacter();

	bool FireGun();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hat")
	UStaticMeshComponent* HatMesh;

	UPROPERTY(EditAnywhere, Category = "Montages")
	UAnimMontage* FireGunMontage;
};
