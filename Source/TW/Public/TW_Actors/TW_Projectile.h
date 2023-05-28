// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TW_Projectile.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;
class USoundCue;

UCLASS()
class TW_API ATW_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ATW_Projectile();
	
	void ScaleDamage(float Scale){Damage *= Scale;}
	
protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	void StartDestroyTimer();

	void DestroyTimerFinished();
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UBoxComponent* Projectile;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UNiagaraComponent* SmokeTrail;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UNiagaraSystem* ProjectileImpact;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage = 25.f;

	FTimerHandle DestroyTimer;
};
