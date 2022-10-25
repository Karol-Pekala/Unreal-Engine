// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "EvolveCharacter.h"

UBTService_PlayerInRange::UBTService_PlayerInRange()
{
	NodeName = TEXT("Is Player In Range");
}

void UBTService_PlayerInRange::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AEvolveCharacter* AIPawn = Cast<AEvolveCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!PlayerPawn || !AIPawn)
	{
		return;
	}
	if ((PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Size() < AIPawn->MaxRange) 
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
