// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TentsCharacter.h"
#include "WaterSource.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TentsHUD.generated.h"

/**
 * 
 */
UCLASS()
class TENTS_API ATentsHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD();

	FVector2D InitialPoint;		//Mouse position when pressed
	FVector2D CurrentPoint;		//Mouse position while holding

	FVector2D InitialPointInteract;	
	FVector2D CurrentPointInteract;

	FVector2D GetMousePos2D();

	UPROPERTY()
	bool bStartSelecting = false;

	UPROPERTY()
	bool bStartInteract = false;

	UPROPERTY()
	TArray <ATentsCharacter*> FoundActors;

	UPROPERTY()
	TArray <AWaterSource*> FoundWaterSource;
	
};
