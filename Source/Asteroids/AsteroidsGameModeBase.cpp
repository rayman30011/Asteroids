// Copyright Epic Games, Inc. All Rights Reserved.


#include "AsteroidsGameModeBase.h"

#include "Player/AsteroidsPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogAsteroidsGameMode, All, All)

void AAsteroidsGameModeBase::PlayerDestroy(AController* PlayerController)
{
	UE_LOG(LogAsteroidsGameMode, Display, TEXT("Player Destroy"));
	if (!PlayerController) return;

	const auto PlayerState = PlayerController->GetPlayerState<AAsteroidsPlayerState>();
	check(PlayerState);
	
	PlayerState->DecreaseHealth();
	
	if (PlayerState->IsDead())
	{
		GameOver();
	}
	else
	{
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, [PlayerController, this]()
		{
			UE_LOG(LogAsteroidsGameMode, Display, TEXT("Player Reset"));
			RestartPlayer(PlayerController);
		}, 2.f, false);
	}
}

void AAsteroidsGameModeBase::StartPlay()
{
	Super::StartPlay();
	OnGameStateChanged.Broadcast(EGameState::InMenu);

	if (DefaultSpaceship)
	{
		SetPlayerDefaults(DefaultSpaceship);
	}
	else
	{
		UE_LOG(LogAsteroidsGameMode, Error, TEXT("DefaultPawn is NULL"));
	}
}

void AAsteroidsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAsteroidsGameModeBase::GameOver()
{
	OnGameOver.Broadcast(nullptr);
	OnGameStateChanged.Broadcast(EGameState::GameOver);
	UE_LOG(LogAsteroidsGameMode, Display, TEXT("GAME OVER"));
}
