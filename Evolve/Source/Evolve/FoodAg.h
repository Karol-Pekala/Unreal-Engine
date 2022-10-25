// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "FoodAg.generated.h"

/**
 * 
 */
UCLASS()
class EVOLVE_API AFoodAg : public AFood
{
	GENERATED_BODY()
	
protected:
	virtual void OnPicked() override;
};
