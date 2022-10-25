// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvolveUpgrade.generated.h"

class APlayerCharacter;
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOLVE_API UEvolveUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEvolveUpgrade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	APlayerCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AgressionNeeded;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MobilityNeeded;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 StrengthNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DamageIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRangeIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float JumpRateIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MomentumIncrement;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEvolveUpgrade> NextUpgradeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UpgradeName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAvailable;

	UFUNCTION(BlueprintCallable)
	void Upgrade();

private:
	void CheckIfAvailable();
		
	void AddNextUpgrade();
};
