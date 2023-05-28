// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TW_EnemyAIController.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;
class AActor;

UCLASS()
class TW_API ATW_EnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATW_EnemyAIController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTargetPerceptionUpdated( AActor* Actor, FAIStimulus Stimulus);

	AActor* GetTargetActor() const { return TargetActor;}
	
private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	AActor* TargetActor;
};
