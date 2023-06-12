// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "Base/Lobby/PlayerControllerLobby.h"
#include "Base/Lobby/PlayerStateLobby.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

void AGameStateLobby::BeginPlay()
{
	Super::BeginPlay();
}

void AGameStateLobby::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	UE_LOG(LogTemp, Warning, TEXT("AddPlayerState called on %s"), GetNetMode() == NM_Client? *FString("Client") : *FString("Server") );
}

void AGameStateLobby::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	UE_LOG(LogTemp, Warning, TEXT("RemovePlayerState called on %s"), GetNetMode() == NM_Client? *FString("Client") : *FString("Server") );

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
