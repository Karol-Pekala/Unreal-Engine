// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "FoodSt.generated.h"

/**
 * 
 */
UCLASS()
class EVOLVE_API AFoodSt : public AFood
{
	GENERATED_BODY()
	

protected:
	virtual void OnPicked() override;
};
