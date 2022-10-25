// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Particles/ParticleSystem.h"
#include "LightsGameMode.h"

void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBeingLit)
	{
		bIsLit = true;
	}
	else
	{
		bIsLit = false;
	}
	bIsBeingLit = false;
}

void ATarget::BeLit(UParticleSystem* RayLit)
{
	Super::BeLit(RayLit);

	if (RayLit == RayNeeded)
	{
		ALightsGameMode* GameMode = GetWorld()->GetAuthGameMode<ALightsGameMode>();
		if (GameMode)
		{
			GameMode->TargetLit();
		}
		UE_LOG(LogTemp, Warning, TEXT("Target Lit"));
	}

}