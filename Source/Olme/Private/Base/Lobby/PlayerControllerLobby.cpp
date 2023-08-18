// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerControllerLobby.h"

#include "UISystemFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/HUDLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/LobbyMenu.h"

void APlayerControllerLobby::UpdatePlayerList_Implementation(const TArray<FLobbyPlayerData>& data, const int32 CurrNrOfPlayers)
{
	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerControllerLobby::UpdatePlayerList_Implementation"));
	
	// If, for some reason, the widget is not ready yet, create it here already before the HUD instance does
	if(AHUDLobby* HudLobby = Cast<AHUDLobby>(GetHUD()))
	{
		HudLobby->TryCreateLobbyMenu();
	}

	// Update the player list
	if(ULobbyMenu* LobbyMenu = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this)))
	{
		LobbyMenu->UpdatePlayerList(data, CurrNrOfPlayers);
	}
}

void APlayerControllerLobby::StartGame_Implementation(const FString& Level)
{
	if(AGameModeLobby* gameMode = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		gameMode->StartGame(Level);
	}
}

void APlayerControllerLobby::BeginPlay()
{
	Super::BeginPlay();

	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerControllerLobby::BeginPlay()"));

	if(UGameplayStatics::GetPlatformName() == "Windows")
	{
		SetShowMouseCursor(true);
	}
}
