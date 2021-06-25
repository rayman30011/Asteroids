// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AsteroidsPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogAsteroidsPlayerState, All, All);

void AAsteroidsPlayerState::DecreaseHealth()
{
	if (Health > 0)
	{
		--Health;
		Health = FMath::Clamp(Health, 0, 3);
		OnLivesChanged.Broadcast(Health);
		UE_LOG(LogAsteroidsPlayerState, Display, TEXT("Heath %d"), Health);
	}
}

void AAsteroidsPlayerState::AddScores(int32 ScoresForAdd)
{
	Scores += ScoresForAdd;
	UE_LOG(LogTemp, Display, TEXT("New Score %d"), Scores);
	OnScoreChanged.Broadcast(Scores);
}

void AAsteroidsPlayerState::BeginPlay()
{
	Super::BeginPlay();
	OnLivesChanged.Broadcast(Health);
}
