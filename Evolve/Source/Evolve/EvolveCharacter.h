// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EvolveCharacter.generated.h"

class UEvolveUpgrade;

UCLASS()
class EVOLVE_API AEvolveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEvolveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void Attack();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Momentum;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* AttackSourcePoint;

	void MoveForward(float AxisValue);

	void JumpUp();

	void MoveRight(float AxisValue);


};
