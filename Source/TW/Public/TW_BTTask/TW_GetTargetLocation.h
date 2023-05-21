// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TW_GetTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class TW_API UTW_GetTargetLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UTW_GetTargetLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
