// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Spaceship.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesChangedSignature, int32, Lives);
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
	int32 Lives;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	TArray<TSubclassOf<UBaseWeapon>> WeaponClasses;
	
	virtual void BeginPlay() override;

public:
	FOnLivesChangedSignature OnLivesChanged;
	FOnDeadSignature OnDead;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsDead() const { return Lives <= 0; }
	int32 GetLives() const { return Lives; }

private:
	void StartFire();
	void EndFire();

	void Turn(float Value);
	void AddForce(float Value);

	void OnTakeAnyDamage();

	UPROPERTY()
	UBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<UBaseWeapon*> AvailableWeapons;
};
