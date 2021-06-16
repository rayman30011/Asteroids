// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Asteroid.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	AAsteroid();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinForce = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxForce = 150.f;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};