// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Animations/TW_PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "TW_Characters/TW_BaseCharacter.h"

void UTW_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BaseCharacter = Cast<ATW_BaseCharacter>(TryGetPawnOwner());
}

void UTW_PlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (BaseCharacter)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(BaseCharacter->GetVelocity());
		bIsAiming = BaseCharacter->CheckIsAiming();
	}
}
