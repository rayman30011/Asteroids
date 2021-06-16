// Fill out your copyright notice in the Description page of Project Settings.


#include "Enitites/Spaceship.h"

#include "Weapons/BaseWeapon.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	
	SetRootComponent(StaticMesh);
	Muzzle->SetupAttachment(RootComponent);
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

	for (auto Class : WeaponClasses)
	{
		const auto Weapon = NewObject<UBaseWeapon>(this, Class);
		if (!Weapon)
		{
			UE_LOG(LogTemp, Error, TEXT("Can not create weapon %s"), *Class->GetName());
			continue;
		}

		AvailableWeapons.Add(Weapon);
	}

	if (AvailableWeapons.Num() > 0)
	{
		CurrentWeapon = AvailableWeapons[0];
	}
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ASpaceship::Turn);
	PlayerInputComponent->BindAxis("Force", this, &ASpaceship::AddForce);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceship::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceship::EndFire);
}

void ASpaceship::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire(this);
}

void ASpaceship::EndFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->EndFire();
}

void ASpaceship::Turn(float Value)
{
	AddActorLocalRotation(FRotator(0, Value * RotationSpeed, 0));
}

void ASpaceship::AddForce(float Value)
{
	if (Value <= 0.f) return;
	StaticMesh->AddImpulse(GetActorForwardVector() * Impulse);
}

void ASpaceship::OnTakeAnyDamage()
{
	if (IsDead()) return;

	OnLivesChanged.Broadcast(--Lives);
	
	if (IsDead())
		OnDead.Broadcast();
}

