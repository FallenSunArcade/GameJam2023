// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Animations/TW_PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UTW_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
}

void UTW_PlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (Pawn)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(Pawn->GetVelocity());
	}
}
