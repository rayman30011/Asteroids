// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

void UBaseWeapon::StartFire(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void UBaseWeapon::Tick()
{
}

void UBaseWeapon::EndFire()
{
}
