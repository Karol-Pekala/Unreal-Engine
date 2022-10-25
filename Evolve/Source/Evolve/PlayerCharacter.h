// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvolveCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EVOLVE_API APlayerCharacter : public AEvolveCharacter
{
	GENERATED_BODY()
		// Sets default values for this character's properties

public:
		APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MobilityPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 AgressionPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 StrengthPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UEvolveUpgrade*> UpgradeTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UEvolveUpgrade*> AllUpgrades;

};
