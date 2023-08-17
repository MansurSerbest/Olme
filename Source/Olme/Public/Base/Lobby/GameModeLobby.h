// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Structs/OlmeStructs.h"
#include "GameModeLobby.generated.h"

class APlayerControllerLobby;
class APlayerStateLobby;
/**
 * 
 */
UCLASS()
class OLME_API AGameModeLobby : public AGameMode
{
	GENERATED_BODY()

public:
	void StartGame(const FString& level);
	void UpdatePlayerList();
	virtual void Logout(AController* Exiting) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

private:
	void GetPlayerData(TArray<FLobbyPlayerData>& data);

private:
	UPROPERTY()
	TArray<APlayerControllerLobby*> LoggedInPlayerControllers;

	// Track this too to have an order of the list of states
	UPROPERTY()
	TArray<APlayerStateLobby*> LoggedInPlayerStates;
};
