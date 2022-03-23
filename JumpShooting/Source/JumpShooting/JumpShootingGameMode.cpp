// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "JumpShootingGameMode.h"
#include "JumpShootingCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "JumpShootingState.h"


AJumpShootingGameMode::AJumpShootingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AJumpShootingGameMode::OnTargetHit()
{
	if (AJumpShootingState* GS = Cast<AJumpShootingState>(GameState))
	{
		GS->Points++;
		UE_LOG(LogTemp, Warning, TEXT("%d Points"), GS->Points);
	}
}
