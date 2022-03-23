// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JumpShootingGameMode.generated.h"

UCLASS(minimalapi)
class AJumpShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJumpShootingGameMode();

	void OnTargetHit();	
};



