// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/TurnBased/PlayerControllerTurnBased.h"
#include "PlayerControllerRPS.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerControllerRPS : public APlayerControllerTurnBased
{
	GENERATED_BODY()

public:
	APlayerControllerRPS();

	UFUNCTION(Client, Reliable)
	void LeaveGame();
};
