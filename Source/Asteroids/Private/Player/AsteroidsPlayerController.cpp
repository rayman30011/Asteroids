// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AsteroidsPlayerController.h"

#include "Enitites/Spaceship.h"
#include "GameFramework/GameModeBase.h"

void AAsteroidsPlayerController::BeginPlay()
{
	OnNewPawn.AddUObject(this, &AAsteroidsPlayerController::OnPawnChanged);

	const auto Spaceship = Cast<ASpaceship>(GetPawn());
	check(Spaceship)
	SubscribeOnSpaceshipDead(Spaceship);
}

void AAsteroidsPlayerController::OnPawnChanged(APawn* NewPawn)
{
	UE_LOG(LogTemp, Display, TEXT("Pawn Changed"));
	SubscribeOnSpaceshipDead(Cast<ASpaceship>(NewPawn));
}

void AAsteroidsPlayerController::SubscribeOnSpaceshipDead(ASpaceship* Spaceship)
{
	if (!Spaceship) return;
	Spaceship->OnDead.AddDynamic(this, &AAsteroidsPlayerController::OnSpaceshipDead);
}

void AAsteroidsPlayerController::OnSpaceshipDead()
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AAsteroidsPlayerController::RestartPlayer, 3.f);
}

void AAsteroidsPlayerController::RestartPlayer()
{
	const auto GameMode = GetWorld()->GetAuthGameMode();
	GameMode->RestartPlayer(this);
}
