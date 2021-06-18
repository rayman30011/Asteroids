// Fill out your copyright notice in the Description page of Project Settings.


#include "Enitites/Spaceship.h"

#include "Asteroids/AsteroidsGameModeBase.h"
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

	OnTakeAnyDamage.AddDynamic(this, &ASpaceship::OnTakeDamage);
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ASpaceship::Turn);
	PlayerInputComponent->BindAxis("Force", this, &ASpaceship::AddForce);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceship::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceship::EndFire);
}

void ASpaceship::ChangeWeapon(int32 Index)
{
	if (Index >= 0 && Index < AvailableWeapons.Num())
	{
		CurrentWeapon = AvailableWeapons[Index];
	}
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

void ASpaceship::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	OnDead.Broadcast();
	const auto GameMode = GetWorld()->GetAuthGameMode<AAsteroidsGameModeBase>();
	if (GameMode)
	{
		GameMode->PlayerDestroy(GetController());
	}
	Destroy();
}

