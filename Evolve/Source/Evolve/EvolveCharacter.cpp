// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolveCharacter.h"
#include "Components/InputComponent.h"
#include "EvolveUpgrade.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AEvolveCharacter::AEvolveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSourcePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Attack Source Point"));
	AttackSourcePoint->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AEvolveCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	bIsAttacking = false;
	
}

// Called every frame
void AEvolveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bIsAttacking)
	{
		bIsAttacking = false;
	}
	/*if (IsDead())
	{
		Destroy();
	}*/

}

// Called to bind functionality to input
void AEvolveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEvolveCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEvolveCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AEvolveCharacter::JumpUp);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AEvolveCharacter::Attack);

}

void AEvolveCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * Speed);
}

void AEvolveCharacter::JumpUp()
{
	GetCharacterMovement()->JumpZVelocity = JumpRate;
	Jump();
}

void AEvolveCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * Speed);
}

void AEvolveCharacter::Attack()
{
	FVector Location;
	FRotator Rotation;
	GetActorEyesViewPoint(Location, Rotation);
	Location = AttackSourcePoint->GetComponentLocation();
	FHitResult Hit;
	FVector End = Location + Rotation.Vector() * MaxRange;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		bIsAttacking = true;
		AActor* HitActor = Hit.GetActor();
		AController* OwnerController = GetController();
		if (HitActor && OwnerController)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, -Rotation.Vector(), nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			UE_LOG(LogTemp, Warning, TEXT("Actor Hit"));
		}
	}
}

float AEvolveCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;

	if (IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AEvolveCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}
