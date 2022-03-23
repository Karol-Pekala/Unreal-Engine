// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(ItemMesh);

	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
	Active = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

void AItem::Use(AJumpShootingCharacter * Character)
{
}

void AItem::PickedUp()
{
	Active = false;
	SetActorHiddenInGame(true);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
