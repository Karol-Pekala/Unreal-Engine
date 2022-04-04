// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure.h"
#include "GreatTent.generated.h"

/**
 * 
 */
UCLASS()
class TENTS_API AGreatTent : public AStructure
{
	GENERATED_BODY()

public:

	void ReceiveWater(float CarriedWater);

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:

	bool IsLookingForOwner;
};
