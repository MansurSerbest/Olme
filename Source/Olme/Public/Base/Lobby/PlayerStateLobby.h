// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/OlmeStructs.h"
#include "PlayerStateLobby.generated.h"

struct FLobbyPlayerData;

/**
 * 
 */
UCLASS()
class OLME_API APlayerStateLobby : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerStateLobby();
	
	virtual FString GetPlayerNameCustom() const override;

	void GetPlayerData(FLobbyPlayerData& Data);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(Server, Reliable)
	void Server_SetCustomName(const FText& Name);
	
private:
	UPROPERTY(Replicated)
	FLobbyPlayerData PlayerData;
};
