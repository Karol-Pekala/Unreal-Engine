// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure.h"
#include "Components/StaticMeshComponent.h"
#include "TentsPlayerController.h"

// Sets default values
AStructure::AStructure()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StructureMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StructureMesh);

	MaxHealth = 400.f;;
	CurrentHealth = 400.f;
}

// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStructure::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

