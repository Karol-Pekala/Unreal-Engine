// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LightsGameMode.generated.h"

UCLASS(minimalapi)
class ALightsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALightsGameMode();

	void TargetLit();

private:
	void EndGame(bool bIsPlayerWinner);
};



