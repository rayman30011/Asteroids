// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWeapon.generated.h"

/**
 * Базовый класс для оружия
 */
UCLASS(BlueprintType, Blueprintable)
class ASTEROIDS_API UBaseWeapon : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void StartFire(AActor* Instigator);
	
	/** Для ежесекундной логики */
	virtual void Tick();
	
	virtual void EndFire();
};
