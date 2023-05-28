// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_BTTask/TW_FIreAtTarget.h"

#include "Kismet/GameplayStatics.h"
#include "TW_Actors/TW_Gun.h"
#include "TW_Characters/TW_BaseCharacter.h"
#include "AIController.h"


UTW_FIreAtTarget::UTW_FIreAtTarget()
{
	NodeName = TEXT("Fire At Target");
}

EBTNodeResult::Type UTW_FIreAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	

	ATW_BaseCharacter* OwningCharacter = Cast<ATW_BaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if(!OwningCharacter)
	{
		return EBTNodeResult::Failed;
	}
	OwningCharacter->SetIsAiming(true);
    OwningCharacter->FireGun();
	return EBTNodeResult::Succeeded;
}
