// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Structs/OlmeStructs.h"
#include "GameStateLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AGameStateLobby : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	void GetLobbyPlayerData(TArray<FLobbyPlayerData>& OutPlayerData);
};
