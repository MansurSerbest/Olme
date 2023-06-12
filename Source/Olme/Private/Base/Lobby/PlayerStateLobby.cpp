// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerStateLobby.h"

#include "AccountManagerFunctions.h"
#include "Base/Lobby/GameModeLobby.h"
#include "Base/Lobby/PlayerControllerLobby.h"
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

	DOREPLIFETIME(APlayerStateLobby, NameCustom);
}

FString APlayerStateLobby::GetPlayerNameCustom() const
{
	return NameCustom;
}

void APlayerStateLobby::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetNetMode() == NM_Client)
	{
		Server_SetCustomName(UAccountManagerFunctions::GetPlayfabUsername(this));
		UE_LOG(LogOlme, Warning, TEXT("Beginplay in Client!"))
	}

	if(GetNetMode() == NM_ListenServer && HasAuthority())
	{
		Server_SetCustomName(UAccountManagerFunctions::GetPlayfabUsername(this));
		UE_LOG(LogOlme, Warning, TEXT("Beginplay in Listen Server + Authority!"))
	}
}

void APlayerStateLobby::OnRep_NameCustom()
{
	Server_UpdatePlayerList();
}

void APlayerStateLobby::Server_UpdatePlayerList_Implementation()
{
	if(AGameModeLobby* GM = Cast<AGameModeLobby>(UGameplayStatics::GetGameMode(this)))
	{
		GM->UpdatePlayerList();
	}
}

void APlayerStateLobby::Server_SetCustomName_Implementation(const FString& Name)
{
	NameCustom = Name;

	switch (GetNetMode())
	{
	case NM_ListenServer:
		UE_LOG(LogOlme, Warning, TEXT("Set name called on NM_ListenServer!"));
		break;
	case NM_Client:
		UE_LOG(LogOlme, Warning, TEXT("Set name called on NM_Client!"));
		break;
	case NM_Standalone:
		UE_LOG(LogOlme, Warning, TEXT("Set name called on NM_Standalone!"));
		break;
	case NM_DedicatedServer:
		UE_LOG(LogOlme, Warning, TEXT("Set name called on NM_DedicatedServer!"));
		break;
	case NM_MAX:
		UE_LOG(LogOlme, Warning, TEXT("Set name called on NM_MAX!"));
		break;
	}
}
