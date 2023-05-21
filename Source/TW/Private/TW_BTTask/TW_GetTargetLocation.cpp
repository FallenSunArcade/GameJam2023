// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_BTTask/TW_GetTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UTW_GetTargetLocation::UTW_GetTargetLocation()
{
	NodeName = TEXT("Get Target Location");
}

EBTNodeResult::Type UTW_GetTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			const FVector PlayerLocation = Player->GetActorLocation();
			Controller->GetBlackboardComponent()->SetValueAsVector("TargetLocation", PlayerLocation);
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}
