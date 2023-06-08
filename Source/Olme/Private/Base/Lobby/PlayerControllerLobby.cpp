// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerControllerLobby.h"

#include "UISystemFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/LobbyMenu.h"

void APlayerControllerLobby::UpdatePlayerList_Implementation()
{
	if(ULobbyMenu* LobbyMenu = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this)))
	{
		if(AGameStateLobby* GameState = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(this)))
		{
			TArray<FLobbyPlayerData> PlayerDataArr;
			GameState->GetLobbyPlayerData(PlayerDataArr);
			LobbyMenu->UpdatePlayerList(PlayerDataArr);
		}
	}
}

void APlayerControllerLobby::BeginPlay()
{
	Super::BeginPlay();
}
