// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightActor.generated.h"

UCLASS()
class LIGHTS_API ALightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeLit(UParticleSystem* RayLit);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	bool bIsBeingLit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsLit;

};
