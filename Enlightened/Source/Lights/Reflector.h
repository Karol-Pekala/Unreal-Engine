// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightActor.h"
#include "Reflector.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTS_API AReflector : public ALightActor
{
	GENERATED_BODY()

public:
	AReflector();

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* Ray;

	UPROPERTY(EditAnywhere)
	USceneComponent* RaySpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RayLength;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
