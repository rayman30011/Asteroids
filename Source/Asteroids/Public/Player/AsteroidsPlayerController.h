// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Asteroids/AsteroidsGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "AsteroidsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnGameStateChanged(EGameState GameState);
};
