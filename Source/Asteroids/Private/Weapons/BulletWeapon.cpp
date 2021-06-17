// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/BulletWeapon.h"
#include "Enitites/Spaceship.h"


void UBulletWeapon::StartFire(AActor* Instigator)
{
	Super::StartFire(Instigator);
	
	UE_LOG(LogTemp, Warning, TEXT("Fire buller"));
	if (!Instigator || !Instigator->GetWorld()) return;

	const auto Spaceship = Cast<ASpaceship>(Instigator);
	const auto Location = Spaceship ? Spaceship->GetMuzzleWorldLocation() : Instigator->GetActorLocation();
	const auto Rotation = Instigator->GetActorRotation();
	const auto Projectile = Instigator->GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);
	if (Projectile)
	{
		Projectile->SetOwner(Spaceship);
	}
}

void UBulletWeapon::EndFire()
{
}
