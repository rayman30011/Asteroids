// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "BulletWeapon.generated.h"

/**
 * Оружие стреляющее пулями
 */
UCLASS(BlueprintType, Blueprintable)
class ASTEROIDS_API UBulletWeapon : public UBaseWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;
	
public:
	virtual void StartFire(AActor* Instigator) override;
	virtual void EndFire() override;

private:
	void SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, UWorld* World) const;
};
