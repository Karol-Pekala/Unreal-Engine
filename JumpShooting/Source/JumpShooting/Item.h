// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class JUMPSHOOTING_API AItem : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AItem();

	/*UPROPERTY(Transient)
	class UWorld* World;

	virtual class UWorld* GetWorld() const { return World; };*/

	/*The text for using the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	/*The mesh to display this item pickup*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMeshComponent* ItemMesh;

	/*The thumbnail for this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	/*The display name for item in inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	/*Optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	//The inventory that owns this item
	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	/*Blueprint function*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AJumpShootingCharacter* Character);

	/*Is Item still pickable or is it already picked up*/
	UPROPERTY()
	bool Active;

	virtual void Use(class AJumpShootingCharacter* Character);

	void PickedUp();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
