// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Machine.generated.h"

UCLASS()
class JUMPSHOOTING_API AMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachine();


	/*The mesh to display this machine*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Machine")
	class UStaticMeshComponent* MachineMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* Music;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void TurnOn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
