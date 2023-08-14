// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerStateLobby.h"

#include "AccountManagerFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Olme/Olme.h"

APlayerStateLobby::APlayerStateLobby()
{
	bUseCustomPlayerNames = true;
}

void APlayerStateLobby::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateLobby, PlayerData);
}

FString APlayerStateLobby::GetPlayerNameCustom() const
{
	return PlayerData.DisplayName.ToString();
}

void APlayerStateLobby::GetPlayerData(FLobbyPlayerData& Data)
{
	Data = PlayerData;
}

void APlayerStateLobby::BeginPlay()
{
	Super::BeginPlay();

	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerStateLobby::BeginPlay()"));

	PlayerData.DisplayName = FText::FromString(UAccountManagerFunctions::GetPlayfabUsername(this));
	APlayerControllerLobby* pc = Cast<APlayerControllerLobby>(UGameplayStatics::GetPlayerController(this, 0));
	
	// The client which connected to the (listen)-server
	if(pc && GetNetMode() == NM_Client && pc->IsLocalController())
	{
		Server_SetCustomName(PlayerData.DisplayName);
	}
	// The lobby host
	else if(pc && GetNetMode() == NM_ListenServer && pc->IsLocalController())
	{
		if(AGameModeLobby* GM = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
		{
			GM->UpdatePlayerList();
		}
	}
}

void APlayerStateLobby::Server_SetCustomName_Implementation(const FText& Name)
{
	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerStateLobby::Server_SetCustomName"));
	PlayerData.DisplayName = Name;

	if(AGameModeLobby* GM = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		GM->UpdatePlayerList();
	}
}
