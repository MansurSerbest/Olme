// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameModeLobby.h"

#include "AccountManagerFunctions.h"
#include "OnlineSessionFunctions.h"
#include "SessionSubsystem.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "Olme/Olme.h"
#include "Structs/OlmeStructs.h"

void AGameModeLobby::OnPostLogin(AController* NewPlayer)
{
	UE_LOG(LogOlme, Log, TEXT("Postlogin! Player: %s"), *NewPlayer->GetName());

	APlayerControllerLobby* PC = Cast<APlayerControllerLobby>(NewPlayer);
	if(PC)
	{
		LoggedInPlayerControllers.Push(PC);
		LoggedInPlayerStates.Push(PC->GetPlayerState<APlayerStateLobby>());
	}

	UpdatePlayerList();
}

void AGameModeLobby::GetPlayerData(TArray<FLobbyPlayerData>& data)
{
	for(auto PS : LoggedInPlayerStates)
	{
		FLobbyPlayerData tempData;
		PS->GetPlayerData(tempData);
		data.Push(tempData);
	}
}

void AGameModeLobby::StartGame(const FString& level)
{
	if(UWorld* World = GetWorld())
	{
		UOnlineSessionFunctions::DestroySession(this);
		World->ServerTravel(level);
	}
}

void AGameModeLobby::UpdatePlayerList()
{
	TArray<FLobbyPlayerData> Data;
	GetPlayerData(Data);
	
	for(APlayerControllerLobby* it : LoggedInPlayerControllers)
	{
		it->UpdatePlayerList(Data);
	}
}

void AGameModeLobby::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	for(int i = 0; i < LoggedInPlayerControllers.Num(); ++i)
	{
		if(Exiting == LoggedInPlayerControllers[i])
		{
			LoggedInPlayerControllers.RemoveAt(i);
			LoggedInPlayerStates.RemoveAt(i);
			break;
		}
	}
	
	// Execute logic only when logout happens during lobby time
	if(!HasMatchEnded())
	{
		if(!Exiting->IsLocalController())
		{
			UpdatePlayerList();
		}
	}
}

void AGameModeLobby::BeginPlay()
{
	Super::BeginPlay();

	// // Remove the cached playercontroller/playerstate if they logout
	// FGameModeEvents::GameModeLogoutEvent.AddLambda([this](AGameModeBase* GameMode, AController* PlayerController)->void
	// {
	// 	// Execute logic only when logout happens during lobby time
	// 	if(!HasMatchEnded())
	// 	{
	// 		for(int i = 0; i < LoggedInPlayerControllers.Num(); ++i)
	// 		{
	// 			if(PlayerController == LoggedInPlayerControllers[i])
	// 			{
	// 				LoggedInPlayerControllers.RemoveAt(i);
	// 				LoggedInPlayerStates.RemoveAt(i);
	// 				break;
	// 			}
	// 		}
	//
	// 		if(!PlayerController->IsLocalController())
	// 		{
	// 			UpdatePlayerList();
	// 		}
	// 	}
	// });
}
