// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolveController.h"
#include "Blueprint/UserWidget.h"

void AEvolveController::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}

}

