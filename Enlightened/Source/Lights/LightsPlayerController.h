// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LightsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTS_API ALightsPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> StartScreenClass;
	
protected:
	virtual void BeginPlay() override;
};
