#pragma once
#include "OnlineSessionStructs.generated.h"

USTRUCT()
struct FOnlineSessionSettingsProxy
{
	GENERATED_BODY()

	bool bIsLanMatch;

	int32 NrOfPlayers;
};
