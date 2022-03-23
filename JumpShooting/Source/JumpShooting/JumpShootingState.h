// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JumpShootingState.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSHOOTING_API AJumpShootingState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AJumpShootingState();
	
	int32 Points;
};
