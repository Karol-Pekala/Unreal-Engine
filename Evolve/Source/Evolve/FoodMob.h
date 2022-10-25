// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "FoodMob.generated.h"

/**
 * 
 */
UCLASS()
class EVOLVE_API AFoodMob : public AFood
{
	GENERATED_BODY()
	

protected:
	virtual void OnPicked() override;
};
