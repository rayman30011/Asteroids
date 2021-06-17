// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
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
	TSubclassOf<AAsteroid> ChildClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinForce = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxForce = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ScoresForAdd = 100;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
