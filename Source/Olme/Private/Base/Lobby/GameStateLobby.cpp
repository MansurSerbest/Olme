// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "UISystemFunctions.h"
#include "Net/UnrealNetwork.h"
#include "UI/Menu/LobbyMenu.h"

void AGameStateLobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameStateLobby, CurrentLevel);
	DOREPLIFETIME(AGameStateLobby, CurrentGameType);
}

void AGameStateLobby::OnRep_CurrentLevel()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdateLevelInfo(CurrentLevel);
	}
}

void AGameStateLobby::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the properties
	if(GetNetMode() == NM_ListenServer)
	{
		const UDataTable* dataTable = DataTableGameType.LoadSynchronous();
		if(IsValid(dataTable))
		{
			// Set the idx and name of the current game type
			TArray<FName> arr = dataTable->GetRowNames();
			CurrentGameType.First = 0;
			CurrentGameType.Second = arr[0];

			// Set the idx and name of the current level
			CurrentLevel.First = 0;
			if(const FLobbyGameTypeData* row = dataTable->FindRow<FLobbyGameTypeData>(CurrentGameType.Second, TEXT("AGameStateLobby::BeginPlay")))
			{
				CurrentLevel.Second = row->Maps[0];
			}
		}
	}
}

void AGameStateLobby::OnRep_GameType()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdateGameTypeInfo(CurrentGameType);
	}
}

FPairIntName AGameStateLobby::GetCurrentLevel() const
{
	return CurrentLevel;
}

FPairIntName AGameStateLobby::GetCurrentGameType() const
{
	return CurrentGameType;
}

void AGameStateLobby::Server_SetCurrentGameType_Implementation(const FPairIntName& Pair)
{
	CurrentGameType = Pair;

	// No need to call the OnRep_xxx function here this function will only be called via the server (listen server) and all the necessary changes
	// that needs to happen to other clients already happen to the host player (owned by listen server)
}

void AGameStateLobby::Server_SetCurrentLevel_Implementation(const FPairIntName& Pair)
{
	CurrentLevel = Pair;

	// No need to call the OnRep_xxx function here this function will only be called via the server (listen server) and all the necessary changes
	// that needs to happen to other clients already happen to the host player (owned by listen server)
}
