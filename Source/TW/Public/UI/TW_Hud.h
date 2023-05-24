// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TW_Hud.generated.h"

class APlayerController;
class UTexture2D;
UCLASS()
class TW_API ATW_Hud : public AHUD
{
	GENERATED_BODY()

public:
	ATW_Hud();
	
	void AddDeadEyeTarget(const FVector& Target);
	
	void ClearDeadEyeTargets();
	
	TArray<FVector> GetDeadEyeTargets() const {return DeadEyeTargets;};

	void SetDeadEye(bool IsDeadEyeOn) { bIsDeadEyeOn = IsDeadEyeOn; }
	
protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditAnywhere, Category = DeadEye)
	UTexture2D* DeadEyeMark;
	
	TArray<FVector> DeadEyeTargets;
	
	bool bIsDeadEyeOn = false;
	
	UPROPERTY()
	APlayerController * PlayerController = nullptr;
};
