// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_Animations/TW_ReloadNotifyState.h"
#include "TW_Characters/TW_BaseCharacter.h"


void UTW_ReloadNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(ATW_BaseCharacter * BaseCharacter = Cast<ATW_BaseCharacter>(MeshComp->GetOwner()))
	{
		BaseCharacter->SetReloadingFlag(true);
	}
}

void UTW_ReloadNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(ATW_BaseCharacter * BaseCharacter = Cast<ATW_BaseCharacter>(MeshComp->GetOwner()))
	{
		BaseCharacter->SetReloadingFlag(false);
		BaseCharacter->FillAmmo();
	}
}
