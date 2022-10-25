// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_RandomLocation::UBTService_RandomLocation()
{
	NodeName = TEXT("Update Random Location");
}

void UBTService_RandomLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn)
	{
		return;
	}
	FVector RandomVector = FMath::VRand();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AIPawn->GetActorLocation()+(FVector(RandomVector.X, RandomVector.Y, 0.f)*100.f));
}