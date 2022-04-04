// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatTent.h"
#include "TentsPlayerController.h"

void AGreatTent::ReceiveWater(float CarriedWater)
{
	if (OwningController != nullptr)
	{
		OwningController->CollectedWater += CarriedWater;
		UE_LOG(LogTemp, Warning, TEXT("Delivered,  %f "), CarriedWater);
	}
}

void AGreatTent::BeginPlay()
{
	Super::BeginPlay();
	IsLookingForOwner = true;
}

void AGreatTent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwningController != nullptr && IsLookingForOwner)
	{
		OwningController->GreatTentLocation = GetActorLocation();
		IsLookingForOwner = false;
	}
}

