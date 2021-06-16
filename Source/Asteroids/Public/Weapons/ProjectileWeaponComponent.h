// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeaponComponent.h"
#include "ProjectileWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UProjectileWeaponComponent : public UBaseWeaponComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;
	
public:
	virtual void StartFire() override;
};
