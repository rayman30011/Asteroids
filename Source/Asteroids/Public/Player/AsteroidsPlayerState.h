// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AsteroidsPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangedSigrature, int32, Score);

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
	
	void AddScores(int32 ScoresForAdd);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Scores = 0;
};
