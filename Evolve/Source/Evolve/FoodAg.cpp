// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodAg.h"
#include "PlayerCharacter.h"

void AFoodAg::OnPicked()
{
	Super::OnPicked();
	if (PlayerCharacter)
	{
		if (PlayerCharacter->AgressionPoints < 5)
		{
			Destroy();
			PlayerCharacter->AgressionPoints++;
		}
	}
}