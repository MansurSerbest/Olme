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

	DOREPLIFETIME(APlayerStateLobby, NameCustom);
}

FString APlayerStateLobby::GetPlayerNameCustom() const
{
	return NameCustom;
}

void APlayerStateLobby::BeginPlay()
{
	Super::BeginPlay();

	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerStateLobby::BeginPlay()"));
	
	if(GetNetMode() == NM_Client)
	{
		Server_SetCustomName(UAccountManagerFunctions::GetPlayfabUsername(this));
	}

	APlayerController* pc = GetPlayerController();
	if(pc && GetNetMode() == NM_ListenServer && pc->IsLocalController())
	{
		Server_SetCustomName(UAccountManagerFunctions::GetPlayfabUsername(this));
	}
}

void APlayerStateLobby::OnRep_NameCustom()
{
	// Get the playercontroller owned by this machine
	if(APlayerControllerLobby* pc = Cast<APlayerControllerLobby>(UGameplayStatics::GetPlayerController(this, 0))) 
	{
		pc->UpdatePlayerList();
	}

	UOlmeHelperFunctions::PrintNetMode(this, TEXT("OnRep_NameCustom"));
}

void APlayerStateLobby::Server_SetCustomName_Implementation(const FString& Name)
{
	NameCustom = Name;
	UOlmeHelperFunctions::PrintNetMode(this, TEXT("APlayerStateLobby::Server_SetCustomName"));
	OnRep_NameCustom();
}
