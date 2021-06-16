// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/BulletWeapon.h"
#include "Enitites/Spaceship.h"


void UBulletWeapon::StartFire(AActor* Instigator, UWorld* World)
{
	Super::StartFire(Instigator, World);
	
	UE_LOG(LogTemp, Warning, TEXT("Fire buller"));
	if (!World || !Instigator) return;
	
	// const auto Spaceship = Cast<ASpaceship>(Instigator);
	// if (Spaceship)
	// {
	// 	SpawnProjectile(Spaceship->GetMuzzleWorldLocation(), Instigator->GetActorRotation(), World);
	// }
	// else
	// {
	// 	SpawnProjectile(Instigator->GetActorLocation(), Instigator->GetActorRotation(), World);
	// }
}

void UBulletWeapon::EndFire()
{
}

void UBulletWeapon::SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, UWorld* World) const
{
	World->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);
}
