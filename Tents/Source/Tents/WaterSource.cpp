// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterSource.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWaterSource::AWaterSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterSourceMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(WaterSourceMesh);

	//MaxWater = 500.f;
	//CurrentWater = 500.f;
	MeshScale.Set(CurrentWater / 100.f, CurrentWater / 100.f, 0.05f);
	WaterSourceMesh->SetRelativeScale3D(MeshScale);
}

// Called when the game starts or when spawned
void AWaterSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWaterSource::GetDrained(float CarriedWater)
{
	if (CurrentWater > CarriedWater + 0.0001f)
	{
		CurrentWater -= CarriedWater;
		MeshScale.Set(CurrentWater / 100.f, CurrentWater / 100.f, 0.05f);
		WaterSourceMesh->SetRelativeScale3D(MeshScale);
		return true;
	}
	else
		return false;
}

