// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 9;
}


bool UInventoryComponent::AddItem(AItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}
	Item->OwningInventory = this;
	Items.Add(Item);

	//Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(AItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	/*On create we add all the default Items to be already in characters Inventory*/
	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	
}



