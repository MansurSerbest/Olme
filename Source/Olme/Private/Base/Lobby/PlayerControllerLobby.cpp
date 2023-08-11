// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerControllerLobby.h"

#include "UISystemFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/HUDLobby.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/LobbyMenu.h"

void APlayerControllerLobby::UpdatePlayerList()
{
	// If, for some reason, the widget is not ready yet, create it here already before the HUD instance does
	if(AHUDLobby* HudLobby = Cast<AHUDLobby>(GetHUD()))
	{
		HudLobby->TryCreateLobbyMenu();
	}

	// Update the player list
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

void APlayerControllerLobby::StartGame_Implementation(const FString& level)
{
	if(AGameModeLobby* gameMode = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		gameMode->StartGame(level);
	}
}

void APlayerControllerLobby::BeginPlay()
{
	Super::BeginPlay();

	if(UGameplayStatics::GetPlatformName() == "Windows")
	{
		SetShowMouseCursor(true);
	}
}
