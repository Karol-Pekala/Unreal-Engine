// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodMob.h"
#include "PlayerCharacter.h"

void AFoodMob::OnPicked()
{
	Super::OnPicked();
	if (PlayerCharacter)
	{
		if (PlayerCharacter->MobilityPoints < 5)
		{
			Destroy();
			PlayerCharacter->MobilityPoints++;
		}
	}
}
