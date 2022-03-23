// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	SetRootComponent(PlatformMesh);

	Lift = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z <= 400.f)
		Lift = true;
	if (GetActorLocation().Z >= 1000.f)
		Lift = false;
	FVector Falling(0.f, 0.f, -2.f);
	FVector Lifting(0.f, 0.f, 2.f);
	if(Lift)
		AddActorWorldOffset(Lifting, false);
	else
		AddActorWorldOffset(Falling, false);
}

