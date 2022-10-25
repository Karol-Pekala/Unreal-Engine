// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Reflector.h"
#include "Mirror.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTS_API AMirror : public AReflector
{
	GENERATED_BODY()

public:
	
	virtual void BeLit(UParticleSystem* RayLit) override;

	virtual void Tick(float DeltaTime) override;
};
