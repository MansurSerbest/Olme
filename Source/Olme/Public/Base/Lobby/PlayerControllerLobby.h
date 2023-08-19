// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerControllerLobby : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void UpdatePlayerList(const TArray<FLobbyPlayerData>& data, const int32 CurrNrOfPlayers);

	UFUNCTION(Server, Reliable)
	void StartGame(const FString& Level);

	UFUNCTION(Client, Reliable)
	void LeaveLobby();
protected:
	virtual void BeginPlay() override;

	// Level that should open after quitting the lobby
	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UWorld> LevelAfterQuitLobby;
};
