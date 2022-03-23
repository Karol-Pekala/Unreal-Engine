// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AMachine::AMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MachineMesh = CreateDefaultSubobject<UStaticMeshComponent>("MachineMesh");
	SetRootComponent(MachineMesh);

}

// Called when the game starts or when spawned
void AMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMachine::TurnOn()
{
	UGameplayStatics::PlaySoundAtLocation(this, Music, GetActorLocation());
}

// Called every frame
void AMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

