// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AsteroidsPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangedSigrature, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLivesChangedSigrature, int32, Lives);

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FScoreChangedSigrature OnScoreChanged;

	UPROPERTY(BlueprintAssignable)
	FLivesChangedSigrature OnLivesChanged;
	
	int32 GetHealth() const { return Health; }
	bool IsDead() const { return Health <= 0; }
	void DecreaseHealth();

	void AddScores(int32 ScoresForAdd);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Scores = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Health = 3;
};
