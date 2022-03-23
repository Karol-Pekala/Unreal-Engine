// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "JumpShootingCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Machine.h"
#include "UserWidget.h"

//////////////////////////////////////////////////////////////////////////
// AJumpShootingCharacter

AJumpShootingCharacter::AJumpShootingCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 9;

	//Sphere aroud player that marks pick up range
	CollectionRange = CreateDefaultSubobject<USphereComponent>("CollectionRange");
	CollectionRange->AttachTo(RootComponent);
	CollectionRange->SetSphereRadius(250.f);

	//Loading bullets
	Loaded = false;
	LoadingTime = 0;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJumpShootingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Load", IE_Pressed, this, &AJumpShootingCharacter::Load);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AJumpShootingCharacter::Shoot);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AJumpShootingCharacter::Pickup);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJumpShootingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJumpShootingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJumpShootingCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJumpShootingCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJumpShootingCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJumpShootingCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AJumpShootingCharacter::OnResetVR);
}


void AJumpShootingCharacter::UseItem(AItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this);	//Blueprint
	}

}

void AJumpShootingCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (InformationWidgetClass != nullptr)
	{
		InformationWidget = CreateWidget(GetWorld(), InformationWidgetClass);
		InformationWidget->AddToViewport();
	}
}

// Called every frame
void AJumpShootingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Loaded && LoadingTime<100)
		LoadingTime++;
}

void AJumpShootingCharacter::ServerShoot_Implementation()
{
	Shoot();
}

void AJumpShootingCharacter::Shoot()
{
	if (Role < ROLE_Authority)
	{
		ServerShoot();
		return;
	}

	//Checking if we spawn bullet blueprint object correctly
	if (Bullet_BP)
	{
		//Getting actors position for bullet to spawn
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetActorForwardVector() * 100.f + GetActorLocation());
		SpawnTransform.SetRotation(GetActorRotation().Quaternion());
		SpawnTransform.SetScale3D(FVector(1.f));

		//Bullet's parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<ABullet>(Bullet_BP, SpawnTransform, SpawnParams);
		Loaded = false;
		UE_LOG(LogTemp, Warning, TEXT("Loading Time  %f"), LoadingTime);
		LoadingTime = 0;
	}
}

void AJumpShootingCharacter::Load()
{
	Loaded = true;
}

void AJumpShootingCharacter::ServerPickup_Implementation()
{
	Pickup();
}

void AJumpShootingCharacter::Pickup()
{
	if (Role < ROLE_Authority)
	{
		ServerPickup();
		return;
	}

	//Getting all actors within CollectionRange from the character
	TArray<AActor*> NearbyItems;
	CollectionRange->GetOverlappingActors(NearbyItems);

	for (int i = 0; i < NearbyItems.Num(); i++)
	{
		//Checking if Item is still active - if it hasn't been picked up yet
		AItem* const Item = Cast<AItem>(NearbyItems[i]);
		if (Item && Item->Active)
		{
			Item->PickedUp();
			Inventory->AddItem(Item);
			UE_LOG(LogTemp, Warning, TEXT("Item picked up!"));
		}
		//Checking if it is Machine
		AMachine* const Machine = Cast<AMachine>(NearbyItems[i]);
		if (Machine && Inventory->Items.Num())
		{
			Machine->TurnOn();
			UE_LOG(LogTemp, Warning, TEXT("Music playing!"));
		}
	}
}

void AJumpShootingCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJumpShootingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AJumpShootingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AJumpShootingCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJumpShootingCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJumpShootingCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJumpShootingCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
