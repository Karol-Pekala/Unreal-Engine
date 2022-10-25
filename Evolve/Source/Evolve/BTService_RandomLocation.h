// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class EVOLVE_API UBTService_RandomLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_RandomLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

};
