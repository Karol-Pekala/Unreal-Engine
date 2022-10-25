// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolveUpgrade.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UEvolveUpgrade::UEvolveUpgrade()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AgressionNeeded = 0;
	MobilityNeeded = 0;
	StrengthNeeded = 0;
	UpgradeName = FString("Name");
	bIsAvailable = false;

	DamageIncrement = 0;
	SpeedIncrement = 0;
	HealthIncrement = 0;
	MaxRangeIncrement = 0;
	JumpRateIncrement = 0;
	MomentumIncrement = 0;
}


// Called when the game starts
void UEvolveUpgrade::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());	
}


// Called every frame
void UEvolveUpgrade::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckIfAvailable();

}

void UEvolveUpgrade::Upgrade()
{
	if (bIsAvailable)
	{
		PlayerCharacter->AgressionPoints -= AgressionNeeded;
		PlayerCharacter->MobilityPoints -= MobilityNeeded;
		PlayerCharacter->StrengthPoints -= StrengthNeeded;
		PlayerCharacter->Damage += DamageIncrement;
		PlayerCharacter->Speed += SpeedIncrement;
		PlayerCharacter->MaxHealth += HealthIncrement;
		PlayerCharacter->Momentum += MomentumIncrement;
		PlayerCharacter->JumpRate += JumpRateIncrement;
		PlayerCharacter->MaxRange += MaxRangeIncrement;

	}
	AddNextUpgrade();

}

void UEvolveUpgrade::CheckIfAvailable()
{
	if (PlayerCharacter)
	{
		if (PlayerCharacter->AgressionPoints >= AgressionNeeded &&
			PlayerCharacter->MobilityPoints >= MobilityNeeded &&
			PlayerCharacter->StrengthPoints >= StrengthNeeded)
		{
			bIsAvailable = true;
		}
		else
		{
			bIsAvailable = false;
		}
	}
}

void UEvolveUpgrade::AddNextUpgrade()
{
	if (PlayerCharacter)
	{
		UEvolveUpgrade* NextUpgrade;
		PlayerCharacter->UpgradeTree.Remove(this);
		for (UEvolveUpgrade* Upgrade : PlayerCharacter->AllUpgrades)
		{
			if (Upgrade->GetClass() == NextUpgradeClass)
			{
				PlayerCharacter->UpgradeTree.Add(Upgrade);
				NextUpgrade = Upgrade;
			}
		}
		PlayerCharacter->AllUpgrades.Remove(NextUpgrade);
		/*for (UEvolveUpgrade* Upgrade : PlayerCharacter->UpgradeTree)
		{
			UE_LOG(LogTemp, Warning, TEXT("Class: %s %s"), *Upgrade->GetClass()->GetName(), Upgrade->bIsAvailable? TEXT("true") : TEXT("false"));
		}*/
		DestroyComponent();
	}
}

