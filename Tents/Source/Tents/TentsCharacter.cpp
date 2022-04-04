// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TentsCharacter.h"
#include "TentsPlayerController.h"
#include "WaterSource.h"
#include "GreatTent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATentsCharacter::ATentsCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetVisibility(false);

	//Sphere aroud player that marks pick up range
	InteractionRange = CreateDefaultSubobject<USphereComponent>("InteractionRange");
	InteractionRange->AttachTo(RootComponent);
	InteractionRange->SetSphereRadius(200.f);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Initial unit's properties - overwritten in each classes constructor
	MaxHealth = 100.f;
	CurrentHealth = 50.f;
	DehydrationRate = 0.05f;
	NeededWater = 0.009f;
	CarriedWater = 4.f;
	IsCarringWater = false;
	DrainingFlag = false;
	DeliveringFlag = false;
	RunningFlag = false;
}

void ATentsCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (DrainingFlag)
	{
		Drain();
		if (IsCarringWater)
		{
			DrainingFlag = false;
			RunningFlag = true;
		}
	}
	if (RunningFlag)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), OwningController->GreatTentLocation);
		RunningFlag = false;
		DeliveringFlag = true;
	}

	if (DeliveringFlag)
	{
		Deliver();
		if (!IsCarringWater)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), DestinationLocation);
			DeliveringFlag = false;
			DrainingFlag = true;
		}
	}

	Drink();

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ATentsCharacter::SetSelected()
{
	CursorToWorld->SetVisibility(true);

}

void ATentsCharacter::SetDeselected()
{
	CursorToWorld->SetVisibility(false);
}

// If unable to get CollectedWater from Controller of drink CarriedWater, unit loses health equal to DehydrationRate
void ATentsCharacter::Drink()
{
	if (OwningController != nullptr)
	{
		if (OwningController->GetWater(NeededWater))
			return;
	}
	if (CurrentHealth >= DehydrationRate + 0.001f)
		CurrentHealth -= DehydrationRate;
	return;
}

void ATentsCharacter::Drain()
{

	//Getting all actors within InteractionRange from the character
	TArray<AActor*> NearbyActors;
	InteractionRange->GetOverlappingActors(NearbyActors);

	for (int i = 0; i < NearbyActors.Num(); i++)
	{
		AWaterSource* const WaterSource = Cast<AWaterSource>(NearbyActors[i]);
		if (WaterSource && !IsCarringWater)
		{
			if (WaterSource->GetDrained(CarriedWater))
			{
				IsCarringWater = true;
			}
		}
	}
}

void ATentsCharacter::Deliver()
{
	//Getting all actors within InteractionRange from the character
	TArray<AActor*> NearbyActors;
	InteractionRange->GetOverlappingActors(NearbyActors);

	for (int w = 0; w < NearbyActors.Num(); w++)
	{
		AGreatTent* const GreatTent = Cast<AGreatTent>(NearbyActors[w]);
		if (GreatTent && IsCarringWater)
		{
			GreatTent->ReceiveWater(CarriedWater);
			IsCarringWater = false;
		}
	}
}
