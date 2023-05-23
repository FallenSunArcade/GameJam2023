// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "TW_BaseCharacter.h"
#include "TW_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGunFiredDelegate, int32, CurrentGunsAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDamagedDelegate, int32, CurrentPlayerHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeadEyeStartDelegate, int32, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeadEyeEndDelegate, int32, CurrentTime);

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class ATW_Gun;

UCLASS()
class ATW_Player : public ATW_BaseCharacter
{
	GENERATED_BODY()

public:
	ATW_Player();
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void Aim(const FInputActionValue& Value);

	void DeadEye(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void GunWasFired(int32 CurrentGunsAmmo);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerWasDamaged(int32 PlayersCurrentHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void DeadEyeInProgress(int32 CurrentTime);
	
	UFUNCTION(BlueprintImplementableEvent)
	void DeadEyeEnded(int32 CurrentTime);
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintAssignable)
	FGunFiredDelegate GunFired;

	UPROPERTY(BlueprintAssignable)
	FPlayerDamagedDelegate PlayerDamaged;

	UPROPERTY(BlueprintAssignable)
	FDeadEyeStartDelegate StartDeadEye;

	UPROPERTY(BlueprintAssignable)
	FDeadEyeEndDelegate EndDeadEye;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DeadEye")
	int32 MaxDeadEyeTime = 5;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DeadEye")
	int32 CurrentDeadEyeTime = 5;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void UpdateDeadEyeMeter();

	UFUNCTION()
	void UpdateHudAmmo();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DeadEyeAction;

	FTimerHandle UpdateDeadEyeMeterHandle;

	FTimerHandle UpdateAmmoHandle;

	bool bDeadEyeInProgress = false;
};

