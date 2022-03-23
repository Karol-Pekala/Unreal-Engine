// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "JumpShootingGameMode.h"
#include "Target.h"
#include "MovingPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "JumpShootingCharacter.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");

	CharacterRange = CreateDefaultSubobject<USphereComponent>("CollectionRange");
	CharacterRange->AttachTo(RootComponent);
	CharacterRange->SetSphereRadius(250.f);
	TArray<AActor*> NearbyCharacters;
	CharacterRange->GetOverlappingActors(NearbyCharacters);

	for (int i = 0; i < NearbyCharacters.Num(); i++)
	{
		AJumpShootingCharacter* const Shooter = Cast<AJumpShootingCharacter>(NearbyCharacters[i]);
		if (Shooter)
		{
			Speed = Shooter->LoadingTime * 100.f;
			BulletMovement->InitialSpeed = Speed;
			UE_LOG(LogTemp, Warning, TEXT("BulletSpeed  %f"), Speed);
			UE_LOG(LogTemp, Warning, TEXT("Loading %f"), Shooter->LoadingTime);
			BulletMovement->MaxSpeed = 10000.0f;

		}
	}

	BulletMovement->InitialSpeed = Speed;
	UE_LOG(LogTemp, Warning, TEXT("BulletSpeed  %f"), Speed);
	BulletMovement->MaxSpeed = 10000.0f;

	OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::PlaySoundAtLocation(this, Shot, GetActorLocation());
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBulletHit(AActor * SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (ATarget* Target = Cast<ATarget>(OtherActor))
	{
		if (AJumpShootingGameMode* GM = Cast<AJumpShootingGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GM->OnTargetHit();
			Destroy();
		}
	}

	if (AActor* Actor = Cast<AActor>(OtherActor))
	{
		Destroy();
	}
}

