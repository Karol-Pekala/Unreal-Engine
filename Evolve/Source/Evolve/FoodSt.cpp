// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSt.h"
#include "PlayerCharacter.h"

void AFoodSt::OnPicked()
{
	Super::OnPicked();
	if (PlayerCharacter)
	{
		if (PlayerCharacter->StrengthPoints < 5)
		{
			Destroy();
			PlayerCharacter->StrengthPoints++;
		}
	}
}