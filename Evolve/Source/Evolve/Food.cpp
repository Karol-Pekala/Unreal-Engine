// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"


// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodCaps = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Food Capsule"));
	RootComponent = FoodCaps;
	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Food Mesh"));
	FoodMesh->SetupAttachment(RootComponent);
}

void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter && FoodCaps->IsOverlappingActor(PlayerCharacter))
	{
		OnPicked();
	}


}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

void AFood::OnPicked()
{
}


