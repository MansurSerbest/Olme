// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "UISystemFunctions.h"
#include "Net/UnrealNetwork.h"
#include "UI/Menu/LobbyMenu.h"

void AGameStateLobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameStateLobby, CurrentLevelIdx);
}

void AGameStateLobby::OnRep_CurrentLevelIdx()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdateLevelInfo(CurrentLevelIdx);
	}
}

void AGameStateLobby::Server_SetCurrentLevelIdx_Implementation(const int32 idx)
{
	CurrentLevelIdx = idx;
}
