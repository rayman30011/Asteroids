// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/CoreTypes.h"

#include "AsteroidsGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverSignature, AController*, WinnerContoller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState, WinnerContoller);

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangedSignature OnGameStateChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameOverSignature OnGameOver;

	EGameState GetGameState() const { return CurrentState; }
	
	void PlayerDestroy(AController* PlayerController);
	virtual void StartPlay() override;

protected:
	virtual void BeginPlay() override;
	
private:
	void GameOver();
	
	EGameState CurrentState;
};
