// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AsteroidsPlayerController.h"

#include "Enitites/Spaceship.h"
#include "GameFramework/GameModeBase.h"

void AAsteroidsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	const auto GameMode = GetWorld()->GetAuthGameMode<AAsteroidsGameModeBase>();
	if (GameMode)
	{
		GameMode->OnGameStateChanged.AddDynamic(this, &AAsteroidsPlayerController::OnGameStateChanged);
	}
}

void AAsteroidsPlayerController::OnGameStateChanged(EGameState GameState)
{
	if (GameState == EGameState::InPlay)
	{
		SetInputMode(FInputModeGameOnly{});
		SetShowMouseCursor(false);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("PlayerContoller UI Only"));
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly{});
	}
}
