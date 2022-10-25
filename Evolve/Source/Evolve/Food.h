// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

class UCapsuleComponent;
class APlayerCharacter;

UCLASS()
class EVOLVE_API AFood : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFood();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* FoodCaps;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FoodMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerCharacter* PlayerCharacter;

	virtual void OnPicked();


};
