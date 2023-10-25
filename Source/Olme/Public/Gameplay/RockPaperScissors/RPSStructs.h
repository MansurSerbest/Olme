#pragma once
#include "RPSStructs.generated.h"

UENUM(BlueprintType)
enum class ERockPaperScissors
{
	eRock		= 0 UMETA(DisplayName = "Rock"),
	ePaper		= 1 UMETA(DisplayName = "Paper"),
	eScissors	= 2 UMETA(DisplayName = "Scissors"),
	eMax		= 3 UMETA(DisplayName = "Unknown")
};

UENUM(BlueprintType)
enum class ERPSResult
{
	ePlayerOne		= 0 UMETA(DisplayName = "PlayerOne"),
	ePlayerTwo		= 1 UMETA(DisplayName = "PlayerTwo"),
	eDraw			= 2 UMETA(DisplayName = "Draw"),
	eMax			= 3 UMETA(Hidden)
};
