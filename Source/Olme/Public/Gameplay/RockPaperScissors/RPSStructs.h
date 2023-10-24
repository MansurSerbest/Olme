#pragma once
#include "RPSStructs.generated.h"

UENUM(BlueprintType)
enum class ERockPaperScissors
{
	eRock		= 0,
	ePaper		= 1,
	eScissors	= 2,
	eMax		= 3 UMETA(Hidden)
};
