// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Spaceship.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

class UBaseWeapon;

UCLASS()
class ASTEROIDS_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	ASpaceship();

	FVector GetMuzzleWorldLocation() const { return Muzzle->GetComponentLocation(); }

protected:
	UPROPERTY(EditDefaultsOnly, Category=Components)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	USceneComponent* Muzzle;;
	
	UPROPERTY(EditDefaultsOnly, Category=Components)
	float Impulse;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	TArray<TSubclassOf<UBaseWeapon>> WeaponClasses;
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDeadSignature OnDead;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(int32 Index);

private:
	void StartFire();
	void EndFire();

	void Turn(float Value);
	void AddForce(float Value);

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY()
	UBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<UBaseWeapon*> AvailableWeapons;
};
