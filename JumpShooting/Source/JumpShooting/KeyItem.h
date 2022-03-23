// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "KeyItem.generated.h"

UCLASS()
class JUMPSHOOTING_API AKeyItem : public AItem
{
	GENERATED_BODY()
	
protected:

	virtual void Use(class AJumpShootingCharacter* Character) override;

};
