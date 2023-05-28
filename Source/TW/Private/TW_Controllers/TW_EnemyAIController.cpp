// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Controllers/TW_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"


ATW_EnemyAIController::ATW_EnemyAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATW_EnemyAIController::OnTargetPerceptionUpdated);
}

void ATW_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}

	
}

void ATW_EnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->ActorHasTag("Player"))
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			TargetActor = Actor;
			GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", true);
			GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", false);
			//GetBlackboardComponent()->SetValueAsObject("TargetActor", GetOwner());
		}
	}
	
}
