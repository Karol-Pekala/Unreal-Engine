// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TentsPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "TentsCharacter.h"
#include "UserWidget.h"
#include "GreatTent.h"
#include "WaterSource.h"
#include "Engine/World.h"

ATentsPlayerController::ATentsPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATentsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDPtr = Cast<ATentsHUD>(GetHUD());
	CollectedWater = 20.f;
	CollectedWood = 10;
	CollectedLeather = 10;

	if (PlayerHUDClass != nullptr)
	{
		PlayerHUD = CreateWidget(GetWorld(), PlayerHUDClass);
		PlayerHUD->AddToViewport();
	}

}

void ATentsPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ATentsPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ATentsPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ATentsPlayerController::SelectionReleased);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ATentsPlayerController::InteractPressed);
	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ATentsPlayerController::InteractReleased);
	InputComponent->BindAction("Draining", IE_Pressed, this, &ATentsPlayerController::Draining);
	InputComponent->BindAction("Delivering", IE_Pressed, this, &ATentsPlayerController::Delivering);
}

//Selection and moving units
void ATentsPlayerController::SelectionPressed()
{
	HUDPtr->InitialPoint = HUDPtr->GetMousePos2D();
	HUDPtr->bStartSelecting = true;
}

void ATentsPlayerController::SelectionReleased()
{
	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
}

void ATentsPlayerController::InteractPressed()
{
	HUDPtr->InitialPointInteract = HUDPtr->GetMousePos2D();
	HUDPtr->bStartInteract = true;
}



void ATentsPlayerController::InteractReleased()
{
	HUDPtr->bStartInteract = false;
	SelectedWaterSource = HUDPtr->FoundWaterSource;

	if (SelectedActors.Num() > 0)
	{
		for (int32 i = 0; i < SelectedActors.Num(); i++)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			SelectedActors[i]->DestinationLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), SelectedActors[i]->DestinationLocation);
			DrawDebugSphere(GetWorld(), SelectedActors[i]->DestinationLocation, 20, 10, FColor::Green, false, .3f);

			if (SelectedWaterSource.Num() == 1)
			{
				SelectedActors[i]->DrainingFlag = true;
			}
		}
	}
}


void ATentsPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ATentsPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATentsPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATentsPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATentsPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ATentsPlayerController::Draining()
{
	if (SelectedActors.Num() > 0)
	{
		for (int32 w = 0; w < SelectedActors.Num(); w++)
		{
			SelectedActors[w]->Drain();
		}
	}
}

void ATentsPlayerController::Delivering()
{
	if (SelectedActors.Num() > 0)
	{
		for (int32 w = 0; w < SelectedActors.Num(); w++)
		{
			SelectedActors[w]->Deliver();
		}
	}
}

bool ATentsPlayerController::GetWater(float NeededWater)
{
	if (CollectedWater > NeededWater + 0.0001f)
	{
		CollectedWater -= NeededWater;
		return true;
	}
	else 
		return false;
}
