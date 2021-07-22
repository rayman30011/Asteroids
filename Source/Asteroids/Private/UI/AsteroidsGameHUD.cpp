// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AsteroidsGameHUD.h"

#include "Asteroids/AsteroidsGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AAsteroidsGameHUD::BeginPlay()
{
	Super::BeginPlay();

	StateWidgets.Add(EGameState::InPlay, CreateWidget<UUserWidget>(GetWorld(), InPlayWidgetClass));
	StateWidgets.Add(EGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
	StateWidgets.Add(EGameState::InMenu, CreateWidget<UUserWidget>(GetWorld(), InMenuWidgetClass));
	StateWidgets.Add(EGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	
	for (const auto WidgetPair : StateWidgets)
	{
		const auto Widget = WidgetPair.Value;
		if (!Widget) continue;
		
		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	const auto GameMode = GetWorld()->GetAuthGameMode<AAsteroidsGameModeBase>();
	if (!GameMode) return;

	GameMode->OnGameStateChanged.AddDynamic(this, &AAsteroidsGameHUD::OnGameStateChanged);
}

void AAsteroidsGameHUD::OnGameStateChanged(EGameState GameState)
{
	UE_LOG(LogTemp, Display, TEXT("GameStateChanged"));
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
    
	CurrentWidget = StateWidgets.Contains(GameState) ? StateWidgets[GameState] : nullptr;
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
