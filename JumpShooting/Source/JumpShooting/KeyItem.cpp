// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "InventoryComponent.h"

void AKeyItem::Use(class AJumpShootingCharacter* Character)
{
	

	if (OwningInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Key used"));
		
		OwningInventory->RemoveItem(this);
	}
}
