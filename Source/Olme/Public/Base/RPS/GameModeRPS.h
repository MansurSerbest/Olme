// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/TurnBased/GameModeTurnBased.h"
#include "GameModeRPS.generated.h"

class APlayerControllerRPS;
/**
 * 
 */
UCLASS()
class OLME_API AGameModeRPS : public AGameModeTurnBased
{
	GENERATED_BODY()

public:
	AGameModeRPS();

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

private:
	int32 MaxNrOfPlayers;

	TArray<APlayerControllerRPS*> LoggedInPlayerControllers;
};
