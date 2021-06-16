// Copyright Epic Games, Inc. All Rights Reserved.


#include "AsteroidsGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogAsteroidsGameMode, All, All)

void AAsteroidsGameModeBase::PlayerDestroy(AController* PlayerController)
{
	UE_LOG(LogAsteroidsGameMode, Display, TEXT("Player Destroy"));
	if (!PlayerController) return;

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, [PlayerController, this]()
	{
		UE_LOG(LogAsteroidsGameMode, Display, TEXT("Player Reset"));
		RestartPlayer(PlayerController);
	}, 2.f, false);
}
