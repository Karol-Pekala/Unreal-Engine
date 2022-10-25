// Fill out your copyright notice in the Description page of Project Settings.


#include "LightsPlayerController.h"
#include "Blueprint/UserWidget.h"

void ALightsPlayerController::BeginPlay()
{
	UUserWidget* StartScreen = CreateWidget(this, StartScreenClass);
	if (StartScreen)
	{
		StartScreen->AddToViewport();
	}
}

void ALightsPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
}

