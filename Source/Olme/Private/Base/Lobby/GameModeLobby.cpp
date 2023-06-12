// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameModeLobby.h"

#include "Base/Lobby/PlayerControllerLobby.h"
#include "Olme/Olme.h"
#include "UI/Menu/LobbyMenu.h"

void AGameModeLobby::OnPostLogin(AController* NewPlayer)
{
	UE_LOG(LogOlme, Log, TEXT("Postlogin! Player: %s"), *NewPlayer->GetName());
	
	if(APlayerControllerLobby* PC = Cast<APlayerControllerLobby>(NewPlayer))
	{
		LoggedInPlayerControllers.Add(PC);
		for(APlayerControllerLobby* PlayerController : LoggedInPlayerControllers)
		{
			PlayerController->UpdatePlayerList();
		}
	}
}

void AGameModeLobby::UpdatePlayerList()
{
	for(APlayerControllerLobby* PlayerController : LoggedInPlayerControllers)
	{
		PlayerController->UpdatePlayerList();
	}
}

void AGameModeLobby::BeginPlay()
{
	Super::BeginPlay();
}
