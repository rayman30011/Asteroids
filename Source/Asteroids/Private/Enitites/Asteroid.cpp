// Fill out your copyright notice in the Description page of Project Settings.


#include "Enitites/Asteroid.h"

#include "Enitites/Spaceship.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/AsteroidsPlayerController.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	Mesh->SetupAttachment(SphereCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AAsteroid::OnTakeDamage);
	OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnBeginOverlap);
}

void AAsteroid::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	const auto PlayerController = Cast<AAsteroidsPlayerController>(InstigatedBy);
	
	if (ChildClass.Get() && PlayerController)
	{
		const auto Location = GetActorLocation();
		const auto Rotation = GetActorRotation();
		auto FirstRotation = Rotation;
		FirstRotation.Add(0.f, 0.f, 45.f);
		const auto FirstLocation = Location + GetActorForwardVector() * 50.f + GetActorRightVector() * -50.f;
		GetWorld()->SpawnActor(ChildClass, &FirstLocation, &FirstRotation);
		
		auto SecondRotation = Rotation;
		SecondRotation.Add(0.f, 0.f, 45.f);
		const auto SecondLocation = Location + GetActorForwardVector() * 50.f + GetActorRightVector() * 50.f;
		GetWorld()->SpawnActor(ChildClass, &SecondLocation, &SecondRotation);
	}

	Destroy();
}


void AAsteroid::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap"));
	const FDamageEvent DamageEvent;
	OtherActor->TakeDamage(1.f, DamageEvent, nullptr, nullptr);
	Destroy();
}

