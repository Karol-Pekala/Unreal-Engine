// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "TentsCharacter.generated.h"

UCLASS(Blueprintable)
class ATentsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATentsCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/*Sphere around the character marking range that character can interact with objects*/
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
	USphereComponent* InteractionRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentHealth;
	float DehydrationRate;	// Amount of health unit is losing per Tick while unable to drink
	float NeededWater;		// Amount of water needed to be taken every Tick to prevent unit from lossing health
	float CarriedWater;		// Amount of water unit is able to carry around 
	bool IsCarringWater;
	FVector DestinationLocation;

	// Flags for draining water and delivering it to Great Tent
	bool DrainingFlag;
	bool DeliveringFlag;
	bool RunningFlag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ATentsPlayerController* OwningController;

	void SetSelected();

	void SetDeselected();

	void Drink(); // Called every tick, getting and subtracting CollectedWater from Controller

	void Drain(); // Getting water from WaterSource, if called while WaterSource in InteractionRange
	
	void Deliver(); // Delivering CarriedWater to GreatTent

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

