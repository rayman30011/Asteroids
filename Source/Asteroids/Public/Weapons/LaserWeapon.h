// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "LaserWeapon.generated.h"

/**
 * Лазерное оружие. Может поражать несколько объектов
 */
UCLASS(BlueprintType, Blueprintable)
class ASTEROIDS_API ULaserWeapon : public UBaseWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Rate = 1.2f;

public:
	virtual void StartFire(AActor* Instigator) override;

private:
	bool CanTrace = true;
	
	void TraceLaser(AActor* Instigator) const;
	void ReloadCompleted();
};
