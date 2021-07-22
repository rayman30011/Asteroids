#pragma once

#include "CoreTypes.generated.h"

UENUM(BlueprintType)
enum class EGameState: uint8
{
	InPlay,
	Pause,
	GameOver,
	InMenu
};