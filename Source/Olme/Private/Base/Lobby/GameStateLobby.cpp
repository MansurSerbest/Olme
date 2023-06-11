// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "Base/Lobby/PlayerStateLobby.h"

void AGameStateLobby::BeginPlay()
{
	Super::BeginPlay();
}

void AGameStateLobby::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
}

void AGameStateLobby::GetLobbyPlayerData(TArray<FLobbyPlayerData>& OutPlayerData)
{
	TArray<FLobbyPlayerData> PlayerDataArr;
	PlayerDataArr.Reserve(PlayerArray.Num());
	
	for(int32 i = 0; i < PlayerArray.Num(); ++i)
	{
		if(PlayerArray[i])
		{
			FLobbyPlayerData PlayerData;
			PlayerData.ListIdx = i;
			PlayerData.DisplayName = FText::FromString(PlayerArray[i]->GetPlayerNameCustom());
			PlayerDataArr.Add(PlayerData);
		}
	}

	OutPlayerData = PlayerDataArr;
}
