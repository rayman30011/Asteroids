// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/LaserWeapon.h"

#include "DrawDebugHelpers.h"
#include "Enitites/Spaceship.h"
#include "Kismet/KismetSystemLibrary.h"

void ULaserWeapon::StartFire(AActor* Instigator)
{
	if (CanTrace && GetWorld())
	{
		CanTrace = false;
		TraceLaser(Instigator);
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ULaserWeapon::ReloadCompleted, Rate, false);
	}
}

void ULaserWeapon::TraceLaser(AActor* Instigator) const
{
	TArray<FHitResult> Hits;
	const auto Spaceship = Cast<ASpaceship>(Instigator);
	const auto StartLocation = Spaceship ? Spaceship->GetMuzzleWorldLocation() : Instigator->GetActorLocation();
	const auto EndLocation = StartLocation + Instigator->GetActorForwardVector() * 1000;
	TArray<AActor*> Ignore;
	if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, EndLocation, 15.f, TraceTypeQuery1, true, Ignore, EDrawDebugTrace::ForDuration, Hits, true))
	{
		for (auto Hit: Hits)
		{
			const auto Actor = Hit.Actor.Get();
			if (!Actor) return;
			Actor->TakeDamage(2.f, FDamageEvent{}, Spaceship ? Spaceship->GetController() : nullptr, Instigator);
		}
	}
}

void ULaserWeapon::ReloadCompleted()
{
	CanTrace = true;
}
