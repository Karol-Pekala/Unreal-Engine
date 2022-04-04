// Fill out your copyright notice in the Description page of Project Settings.

#include "TentsHUD.h"
#include "Tents.h"
#include "TentsPlayerController.h"

void ATentsHUD::DrawHUD()
{
	if (bStartSelecting)
	{
		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0; i < FoundActors.Num(); i++)
			{
				FoundActors[i]->SetDeselected();
			}
		}
		FoundActors.Empty();
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y, 
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsInSelectionRectangle<ATentsCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);
		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0; i < FoundActors.Num(); i++)
			{
				FoundActors[i]->SetSelected();
			}
		}
	}
	else if (bStartInteract)
	{
		FoundWaterSource.Empty();
		CurrentPointInteract = GetMousePos2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPointInteract.X, InitialPointInteract.Y,
			CurrentPointInteract.X - InitialPointInteract.X, CurrentPointInteract.Y - InitialPointInteract.Y);
		GetActorsInSelectionRectangle<AWaterSource>(InitialPointInteract, CurrentPointInteract, FoundWaterSource, false, false);
	}
}

FVector2D ATentsHUD::GetMousePos2D()
{
	float PosX;
	float PosY;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	
	return FVector2D(PosX, PosY);
}

