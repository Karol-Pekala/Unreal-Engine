// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflector.h"
#include "Kismet/GameplayStatics.h" 
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

AReflector::AReflector()
{
	RaySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ray Spawn Point"));
}

void AReflector::BeginPlay()
{
	Super::BeginPlay();
	bIsLit = true;
}

void AReflector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLit)
	{
		FHitResult Hit;
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(
			Hit,
			GetActorLocation() + GetActorForwardVector() * 2.f,
			GetActorLocation() + GetActorForwardVector() * 10000.f,
			ECollisionChannel::ECC_GameTraceChannel2
		);
		if (bSuccess)
		{
			//DrawDebugPoint(GetWorld(), Hit.Location, 10.f, FColor::Red);
			RaySpawnPoint->SetWorldLocation((Hit.Location + GetActorLocation()) / 2.f);
			//DrawDebugPoint(GetWorld(), RaySpawnPoint->GetComponentLocation(), 10.f, FColor::Red);
			RayLength = (Hit.Location - GetActorLocation()).Size();
			ALightActor* ActorHit = Cast<ALightActor>(Hit.GetActor());
			if (ActorHit)
			{
				ActorHit->BeLit(Ray);
			}
		}
	}
	else
	{
		RayLength = 0.f;
	}
}
