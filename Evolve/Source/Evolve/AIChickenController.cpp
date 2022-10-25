// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChickenController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIChickenController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		FVector RandomVector = FMath::VRand();
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"), GetPawn()->GetActorLocation() + (FVector(RandomVector.X, RandomVector.Y, 0.f)*200.f));
	}
}
