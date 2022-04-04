// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TentsGameMode.h"
#include "TentsPlayerController.h"
#include "TentsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATentsGameMode::ATentsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATentsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}