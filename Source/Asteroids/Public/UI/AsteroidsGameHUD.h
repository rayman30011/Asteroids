// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Asteroids/Public/CoreTypes.h"
#include "GameFramework/HUD.h"
#include "AsteroidsGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InMenuWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InPlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EGameState, UUserWidget*> StateWidgets;

	UPROPERTY();
	UUserWidget* CurrentWidget = nullptr;
	
	UFUNCTION()
	void OnGameStateChanged(EGameState GameState);
};
