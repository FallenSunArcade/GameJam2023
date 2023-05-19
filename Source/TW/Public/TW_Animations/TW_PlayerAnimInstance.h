// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TW_PlayerAnimInstance.generated.h"

class APawn;

UCLASS()
class TW_API UTW_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;

	UPROPERTY()
	APawn* Pawn;
};
