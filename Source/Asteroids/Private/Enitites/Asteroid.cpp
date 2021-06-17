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
	Destroy();
	
	if (ChildClass.Get() && PlayerController)
	{
		const auto Radius = SphereCollision->GetScaledSphereRadius();
		
		const auto Location = GetActorLocation();
		const auto FirstRotation = GetActorRotation() + FRotator(0, -30, 0);
		const auto FirstLocation = Location + GetActorRightVector() * -25.f;
		GetWorld()->SpawnActor(ChildClass, &FirstLocation, &FirstRotation);

		const auto SecondRotation = GetActorRotation() + FRotator(0, 30, 0);
		const auto SecondLocation = Location + GetActorRightVector() * 25.f;
		GetWorld()->SpawnActor(ChildClass, &SecondLocation, &SecondRotation);
	}

}


void AAsteroid::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const auto Spaceship = Cast<ASpaceship>(OtherActor);
	if (!Spaceship) return;
	
	UE_LOG(LogTemp, Display, TEXT("Overlap"));
	const FDamageEvent DamageEvent;
	OtherActor->TakeDamage(1.f, DamageEvent, nullptr, nullptr);
	Destroy();
}

