// Fill out your copyright notice in the Description page of Project Settings.


#include "TW_UI/TW_Hud.h"
#include "Kismet/GameplayStatics.h"
#include "TW_Characters/TW_BaseCharacter.h"

ATW_Hud::ATW_Hud()
{}

void ATW_Hud::AddDeadEyeTarget(const FVector& Target)
{
	DeadEyeTargets.Emplace(Target);
}

void ATW_Hud::ClearDeadEyeTargets()
{
	DeadEyeTargets.Empty();
}

void ATW_Hud::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ATW_Hud::DrawHUD()
{
	Super::DrawHUD();

	if(bIsDeadEyeOn)
	{
		if(PlayerController)
		{
			FVector Location;
			FRotator Rotation;
			PlayerController->GetPlayerViewPoint(Location, Rotation);
			
			
			FVector ShotDirection;
			ShotDirection = -Rotation.Vector();
			FVector End = Location + Rotation.Vector() * 10000;
	
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetOwner());
			FHitResult Hit;

			if(GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
			{
				ATW_BaseCharacter* HitActor = Cast<ATW_BaseCharacter>(Hit.GetActor());
				if (HitActor != nullptr)
				{
					if(!HitActor->IsTagged())
					{
						ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
						FVector TargetLocation = PlayerPawn->GetActorLocation() - HitActor->GetActorLocation();
						HitActor->SetTagVisibility(true, TargetLocation.Rotation(), Hit.Location.Z);
					}
				}
			}
		}
	}
}

