// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightActor.h"
#include "Target.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTS_API ATarget : public ALightActor
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	virtual void BeLit(UParticleSystem* RayLit) override;

	UPROPERTY(EditAnywhere)
	UParticleSystem* RayNeeded;

};
