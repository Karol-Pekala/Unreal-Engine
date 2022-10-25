// Fill out your copyright notice in the Description page of Project Settings.


#include "LightActor.h"

// Sets default values
ALightActor::ALightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
	
	bIsBeingLit = false;
	bIsLit = false;
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightActor::BeLit(UParticleSystem * RayLit)
{
	if (!bIsBeingLit)
	{
		bIsBeingLit = true;
	}
}

