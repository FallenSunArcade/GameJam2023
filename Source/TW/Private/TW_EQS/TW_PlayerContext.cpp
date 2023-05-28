// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_EQS/TW_PlayerContext.h"
#include "GameFramework/Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void UTW_PlayerContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	if (const UObject* QueryObject = QueryInstance.Owner.Get())
	{
		if(const AActor* QueryActor = Cast<AActor>(QueryObject))
		{
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, QueryActor);
		}
	}
}
