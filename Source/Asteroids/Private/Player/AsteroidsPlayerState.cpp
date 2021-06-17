// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AsteroidsPlayerState.h"

void AAsteroidsPlayerState::AddScores(int32 ScoresForAdd)
{
	Scores += ScoresForAdd;
	UE_LOG(LogTemp, Display, TEXT("New Score %d"), Scores);
	OnScoreChanged.Broadcast(Scores);
}
