// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerControllerLobby.h"

#include "UISystemFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/LobbyMenu.h"

PRAGMA_DISABLE_OPTIMIZATION
void APlayerControllerLobby::UpdatePlayerList_Implementation()
{
	if(ULobbyMenu* LobbyMenu = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this)))
	{
		if(AGameStateLobby* GameState = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(this)))
		{
			TArray<FLobbyPlayerData> PlayerDataArr;
			PlayerDataArr.Reserve(GameState->PlayerArray.Num());

			TArray<APlayerState*> PlayerStateArr = GameState->PlayerArray;
			for(int32 i = 0; i < PlayerStateArr.Num(); ++i)
			{
				if(APlayerStateLobby* LobbyPlayerstate = Cast<APlayerStateLobby>(GameState->PlayerArray[i]))
				{
					FLobbyPlayerData PlayerData;
					PlayerData.ListIdx = i;
					PlayerData.DisplayName = FText::FromString(LobbyPlayerstate->GetPlayerNameCustom());
					PlayerDataArr.Add(PlayerData);
				}
			}

			LobbyMenu->UpdatePlayerList(PlayerDataArr);
		}
	}
}
PRAGMA_ENABLE_OPTIMIZATION
void APlayerControllerLobby::OnHudBeginplayFinished_Implementation()
{
	if(AGameModeLobby* GameMode = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnHudBeginplayFinished();
	}
}
