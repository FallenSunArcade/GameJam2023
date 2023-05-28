// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_BTTask/TW_FIreAtTarget.h"

#include "Kismet/GameplayStatics.h"
#include "TW_Actors/TW_Gun.h"
#include "TW_Characters/TW_BaseCharacter.h"
#include "TW_Controllers/TW_EnemyAIController.h"


UTW_FIreAtTarget::UTW_FIreAtTarget()
{
	NodeName = TEXT("Fire At Target");
}

EBTNodeResult::Type UTW_FIreAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	

	if(ATW_BaseCharacter* OwningCharacter = Cast<ATW_BaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if(const ATW_EnemyAIController * EnemyAIController = Cast<ATW_EnemyAIController>(OwnerComp.GetAIOwner()))
		{
			if(const AActor* TargetActor = EnemyAIController->GetTargetActor())
			{
				OwningCharacter->FireGun( TargetActor->GetActorLocation(), TargetActor->GetActorRotation(),
			true, FMath::RandRange(0.1f, .5f));

				return EBTNodeResult::Succeeded;
			}
		}

	}
	
	return EBTNodeResult::Failed;
}
