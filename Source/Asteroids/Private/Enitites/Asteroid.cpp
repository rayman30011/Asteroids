// Fill out your copyright notice in the Description page of Project Settings.


#include "Enitites/Asteroid.h"

#include "Enitites/Spaceship.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	if (ChildClass.Get())
	{
		const auto Location = GetActorLocation();
		GetWorld()->SpawnActor(ChildClass, &Location);
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

