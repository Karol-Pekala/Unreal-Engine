// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"
#include "TentsHUD.h"
#include "GameFramework/PlayerController.h"
#include "TentsPlayerController.generated.h"

UCLASS()
class ATentsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATentsPlayerController();

	// Begin PlayerController interface
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// Distributing Water to all player's units
	bool GetWater(float NeededWater);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CollectedWater;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CollectedWood;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CollectedLeather;

	UPROPERTY()
	ATentsHUD* HUDPtr;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PlayerHUDClass;
	UUserWidget* PlayerHUD;

	FVector GreatTentLocation;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	UPROPERTY()
	TArray <ATentsCharacter*> SelectedActors;

	UPROPERTY()
	TArray <AWaterSource*> SelectedWaterSource;


	// Getting water by each players unit every tick

	// Selecting units
	void SelectionPressed();
	void SelectionReleased();

	// Selecting units' target and objects to interact with
	void InteractPressed();
	void InteractReleased();

	
	// Navigate player to the current mouse cursor location.
	void MoveToMouseCursor();

	//Navigate player to the current touch location. 
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	// Navigate player to the given world location. 
	void SetNewMoveDestination(const FVector DestLocation);

	// Input handlers for SetDestination action. 
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void Draining();
	void Delivering();
};


