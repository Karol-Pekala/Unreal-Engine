// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror.h"

void AMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBeingLit)
	{
		bIsLit = true;
	}
	else
	{
		bIsLit = false;
	}
	bIsBeingLit = false;
}

void AMirror::BeLit(UParticleSystem* RayLit)
{
	Super::BeLit(RayLit);

	if (Ray != RayLit)
	{
		Ray = RayLit;
	}
}