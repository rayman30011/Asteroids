// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UBaseWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual void StartFire();
	virtual void EndFire();
};
