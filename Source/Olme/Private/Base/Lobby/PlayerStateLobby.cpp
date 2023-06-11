// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerStateLobby.h"

#include "AccountManagerFunctions.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "Net/UnrealNetwork.h"

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

	if(HasAuthority())
	{
		NameCustom = UAccountManagerFunctions::GetPlayfabUsername(this);
	}
}

void APlayerStateLobby::OnRep_NameCustom()
{
	if(APlayerControllerLobby* PC = Cast<APlayerControllerLobby>(GetPlayerController()))
	{
		PC->UpdatePlayerList();
	}
}
