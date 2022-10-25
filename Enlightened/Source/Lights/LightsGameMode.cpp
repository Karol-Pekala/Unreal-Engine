// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LightsGameMode.h"
#include "LightsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Target.h"

ALightsGameMode::ALightsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ALightsGameMode::TargetLit()
{
	for (ATarget* Target : TActorRange<ATarget>(GetWorld()))
	{
		if (!Target->bIsLit)
		{
			return;
		}
	}

	EndGame(true);
	UE_LOG(LogTemp, Warning, TEXT("GameEnded"));
}

void ALightsGameMode::EndGame(bool bIsPlayerWinner)
{
	AController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
	}
}
