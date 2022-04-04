// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterSource.generated.h"

UCLASS()
class TENTS_API AWaterSource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterSource();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* WaterSourceMesh;

	FVector MeshScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentWater;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetDrained(float CarriedWater);
};
