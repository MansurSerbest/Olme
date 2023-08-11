// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "Base/Lobby/PlayerControllerLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "GameFramework/GameSession.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Olme/Olme.h"

void AGameStateLobby::BeginPlay()
{
	Super::BeginPlay();
}

void AGameStateLobby::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
}

void AGameStateLobby::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	if(GetNetMode() == NM_Client)
	{
		APlayerControllerLobby* PC = Cast<APlayerControllerLobby>(UGameplayStatics::GetPlayerController(this, 0));
		if(PC)
		{
			PC->UpdatePlayerList();
		}
	}
	else if(GetNetMode() == NM_ListenServer)
	{
		APlayerControllerLobby* PC = Cast<APlayerControllerLobby>(UGameplayStatics::GetPlayerController(this, 0));
		if(PC)
		{
			PC->UpdatePlayerList();
		}
	}
}

void AGameStateLobby::GetLobbyPlayerData(TArray<FLobbyPlayerData>& OutPlayerData)
{
	UOlmeHelperFunctions::PrintNetMode(this, TEXT("AGameStateLobby::GetLobbyPlayerData"));
	
	TArray<FLobbyPlayerData> PlayerDataArr;
	PlayerDataArr.Reserve(PlayerArray.Num());
	
	for(int32 i = 0; i < PlayerArray.Num(); ++i)
	{
		if(PlayerArray[i])
		{
			UE_LOG(LogOlme, Warning, TEXT("[%s]"), *PlayerArray[i]->GetPlayerNameCustom());
			FLobbyPlayerData PlayerData;
			PlayerData.ListIdx = i;
			PlayerData.DisplayName = FText::FromString(PlayerArray[i]->GetPlayerNameCustom());
			PlayerDataArr.Add(PlayerData);
		}
	}

	OutPlayerData = PlayerDataArr;
}
