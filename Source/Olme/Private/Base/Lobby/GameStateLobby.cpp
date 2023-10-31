// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameStateLobby.h"

#include "OnlineSessionFunctions.h"
#include "OnlineSessionStructs.h"
#include "UISystemFunctions.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Olme/Olme.h"
#include "Gameplay/Lobby/UI/LobbyMenu.h"

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
			const FLobbyGameTypeData* row = dataTable->FindRow<FLobbyGameTypeData>(CurrentGameType.Second, TEXT("AGameStateLobby::BeginPlay"));
			if(row)
			{
				CurrentLevel.Second = row->Maps[0];
			}

			// Set the player number info
			MinNumberOfPlayers = row->MinNrOfPlayers;
			MaxNumberOfPlayers = row->MaxNrOfPlayers;
		}

		// Update it in the widget
		ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
		if(Widget)
		{
			Widget->UpdateLevelInfo(CurrentLevel);
			Widget->UpdateGameTypeInfo(CurrentGameType);
			Widget->UpdatePlayerNumberInfo(1, MaxNumberOfPlayers);
		}

		// Call this to update the session with the correct session settings and data
		Server_ChangeGameType_Implementation(0);
	}
}

AGameStateLobby* AGameStateLobby::GetInstance(const UObject* WorldContextObject)
{
	AGameStateLobby* result = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(WorldContextObject));
	if(!IsValid(result))
	{
		UE_LOG(LogOlme, Warning, TEXT("AGameStateLobby::GetInstance: Gamestate Instance is nullptr!"));
	}
	
	return result;
}

void AGameStateLobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameStateLobby, CurrentLevel);
	DOREPLIFETIME(AGameStateLobby, CurrentGameType);
	DOREPLIFETIME(AGameStateLobby, MinNumberOfPlayers);
	DOREPLIFETIME(AGameStateLobby, MaxNumberOfPlayers);
}

void AGameStateLobby::OnRep_CurrentLevel()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdateLevelInfo(CurrentLevel);
	}
}

void AGameStateLobby::Server_ChangeLevel_Implementation(const int32 Direction)
{
	const UDataTable* DatatableGameType = DataTableGameType.LoadSynchronous();
	
	if(IsValid(DatatableGameType))
	{
		// Get all the row values
		FLobbyGameTypeData* rowGameType = DatatableGameType->FindRow<FLobbyGameTypeData>(GetCurrentGameType().Second, TEXT("AGameStateLobby::Server_ChangeLevel_Implementation"));
		if(rowGameType)
		{
			// Make sure the level selection loops over the options (gametype struct has a an array of level names)
			const int newIdx = UOlmeHelperFunctions::ShiftInRotation(rowGameType->Maps.Num(), Direction, GetCurrentLevel().First);
			const FName newName = rowGameType->Maps[newIdx];
			CurrentLevel = {newIdx, newName};

			// Also update the OnRep_??? logic on the server
			OnRep_CurrentLevel();
		}
	}
}

void AGameStateLobby::OnRep_CurrentGameType()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdateGameTypeInfo(CurrentGameType);
	}
}

void AGameStateLobby::Server_ChangeGameType_Implementation(const int32 Direction)
{
	UDataTable* dataTable = DataTableGameType.LoadSynchronous();
	
	if(IsValid(dataTable))
	{
		// Update new GameType info
		const int32 newIdx = UOlmeHelperFunctions::ShiftInRotation(dataTable->GetRowNames().Num(), Direction, CurrentGameType.First);
		const FName newName = dataTable->GetRowNames()[newIdx];
		CurrentGameType = {newIdx, newName};
		// Also update the OnRep logic on server
		OnRep_CurrentGameType();

		// Update new Level info: Reset level idx to zero, because every gametype will show its own list of available levels
		FLobbyGameTypeData* row = dataTable->FindRow<FLobbyGameTypeData>(newName, TEXT("AGameStateLobby::Server_ChangeGameType_Implementation"));
		FPairIntName resultLevel = {0, TEXT("")};
		if(row)
		{
			resultLevel.Second = row->Maps[0];
			CurrentLevel = resultLevel;
			// Also update the OnRep logic on server
			OnRep_CurrentLevel();

			// Update Number of player data
			MinNumberOfPlayers = row->MinNrOfPlayers;
			MaxNumberOfPlayers = row->MaxNrOfPlayers;
			
			// Also update it on the server
			OnRep_MaxNumberOfPlayers();

			// Update the session
			FOnlineSessionSettingsProxy settings;
			settings.bIsLanMatch = true;
			settings.NrOfPlayers = MaxNumberOfPlayers;
			UOnlineSessionFunctions::UpdateSession(this, settings);
		}
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

void AGameStateLobby::OnRep_MaxNumberOfPlayers()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(Widget)
	{
		Widget->UpdatePlayerNumberInfo(PlayerArray.Num(), MaxNumberOfPlayers);
	}
}

int32 AGameStateLobby::GetMaxNumberOfPlayers() const
{
	return MaxNumberOfPlayers;
}

int32 AGameStateLobby::GetMinNumberOfPlayers() const
{
	return MinNumberOfPlayers;
}

int32 AGameStateLobby::GetCurrentNumberOfPlayers() const
{
	return PlayerArray.Num();
}
