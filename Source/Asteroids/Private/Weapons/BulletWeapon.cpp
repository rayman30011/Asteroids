// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/BulletWeapon.h"
#include "Enitites/Spaceship.h"


void UBulletWeapon::StartFire(AActor* Instigator)
{
	Super::StartFire(Instigator);
	
	UE_LOG(LogTemp, Warning, TEXT("Fire buller"));
	if (!Instigator || !Instigator->GetWorld()) return;

	
	const auto Spaceship = Cast<ASpaceship>(Instigator);
	if (Spaceship)
	{
		SpawnProjectile(Spaceship->GetMuzzleWorldLocation(), Instigator->GetActorRotation(), Instigator->GetWorld());
	}
	else
	{
		SpawnProjectile(Instigator->GetActorLocation(), Instigator->GetActorRotation(), Instigator->GetWorld());
	}
}

void UBulletWeapon::EndFire()
{
}

void UBulletWeapon::SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, UWorld* World) const
{
	World->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);
}
