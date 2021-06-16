// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileWeaponComponent.h"

#include "Enitites/Spaceship.h"

void UProjectileWeaponComponent::StartFire()
{
	Super::StartFire();
	
	const auto Spaceship = Cast<ASpaceship>(GetOwner());
	if (!Spaceship || !GetWorld()) return;

	const auto Location = Spaceship->GetMuzzleWorldLocation();
	const auto Rotation = Spaceship->GetActorRotation();
	GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);
}
