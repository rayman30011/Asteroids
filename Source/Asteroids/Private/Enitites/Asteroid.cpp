// Fill out your copyright notice in the Description page of Project Settings.


#include "Enitites/Asteroid.h"

#include "GameFramework/ProjectileMovementComponent.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AAsteroid::OnTakeDamage);

	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		const auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		const auto PlayerLocation = PlayerPawn->GetActorLocation();

		const auto Direction = PlayerLocation - GetActorLocation();
		
		ProjectileMovementComponent->AddForce(Direction.GetSafeNormal() * FMath::RandRange(MinForce, MaxForce));
	}
	
}

void AAsteroid::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Display, TEXT("Destory"));
	Destroy();
}

