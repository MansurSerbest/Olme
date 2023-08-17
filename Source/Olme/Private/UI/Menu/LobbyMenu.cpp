// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LobbyMenu.h"

#include "OnlineSessionFunctions.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "Components/TextBlock.h"

ULobbyMenu::ULobbyMenu(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
}

void ULobbyMenu::UpdatePlayerList(const TArray<FLobbyPlayerData>& PlayerData)
{
	// Clear the list before adding new players
	PlayerInfoList->ClearChildren();
	
	int32 counter = 1;
	for(const FLobbyPlayerData& Data : PlayerData)
	{
		ULobbyPlayerEntry* EntryWidget = CreateWidget<ULobbyPlayerEntry>(GetOwningPlayer(), PlayerInfoEntryClass);
		if(IsValid(EntryWidget))
		{
			EntryWidget->Setup( FText::AsNumber(counter), Data.DisplayName);
			PlayerInfoList->AddChildToVerticalBox(EntryWidget);
		}
		++counter;
	}
}

void ULobbyMenu::Init(const bool isHost)
{
	bIsHost = isHost;
	if(!bIsHost)
	{
		ChooseLevelButtonLeft->SetVisibility(ESlateVisibility::Collapsed);
		ChooseLevelButtonRight->SetVisibility(ESlateVisibility::Collapsed);
		StartGameButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ULobbyMenu::UpdateLevelInfo(const FPairIntName& Pair)
{
	const UDataTable* Datatable = LevelDatatable.LoadSynchronous();
	if(IsValid(Datatable))
	{
		if(FLevelData* row = Datatable->FindRow<FLevelData>(Pair.Second, TEXT("ULobbyMenu::UpdateLevelInfo")))
		{
			LevelName->SetText(row->DisplayName);
			LevelThumbnail->SetBrushFromTexture(row->Thumbnail);
		}
	}
}

void ULobbyMenu::UpdateGameTypeInfo(const FPairIntName& Pair)
{
	const UDataTable* DataTable = GameTypeDatatable.LoadSynchronous();
	if(IsValid(DataTable))
	{
		if(FLobbyGameTypeData* row = DataTable->FindRow<FLobbyGameTypeData>(Pair.Second, TEXT("ULobbyMenu::UpdateGameTypeInfo")))
		{
			GameTypeName->SetText(row->DisplayName);
		}
	}
}

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Assign button logic
	ChooseLevelButtonLeft->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelLeft);
	ChooseLevelButtonRight->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelRight);

	ChooseGameTypeButtonLeft->OnPressed.AddDynamic(this, &ULobbyMenu::ULobbyMenu::ChangeGameTypeLeft);
	ChooseGameTypeButtonRight->OnPressed.AddDynamic(this, &ULobbyMenu::ULobbyMenu::ChangeGameTypeRight);
	
	QuitLobbyButton->OnPressed.AddDynamic(this, &ULobbyMenu::QuitLobby);
	StartGameButton->OnPressed.AddDynamic(this, &ULobbyMenu::StartGame);
	
	// Change level logic
	ChangeGameType(0);
	ChangeLevel(0);
}

void ULobbyMenu::ChangeLevelLeft()
{
	ChangeLevel(-1);
}

void ULobbyMenu::ChangeLevelRight()
{
	ChangeLevel(1);
}

void ULobbyMenu::ChangeGameTypeLeft()
{
	ChangeGameType(-1);
}

void ULobbyMenu::ChangeGameTypeRight()
{
	ChangeGameType(1);
}

void ULobbyMenu::ChangeGameType(int32 direction)
{
	UDataTable* dataTable = GameTypeDatatable.LoadSynchronous();
	
	if(IsValid(dataTable))
	{
		// Update new GameType info
		const int32 newIdx = UOlmeHelperFunctions::ShiftInRotation(dataTable->GetRowNames().Num(), direction, GetCurrentGameType().First);
		const FName newName = dataTable->GetRowNames()[newIdx];
		const FPairIntName resultGameType = {newIdx, newName};
		UpdateGameTypeInfo(resultGameType);

		// Update new Level info: Reset level idx to zero, because every gametype will show its own list of available levels
		FLobbyGameTypeData* row = dataTable->FindRow<FLobbyGameTypeData>(newName, TEXT("ULobbyMenu::ChangeGameType"));
		FPairIntName resultLevel = {0, TEXT("")};
		if(row)
		{
			resultLevel.Second = row->Maps[0];
			UpdateLevelInfo(resultLevel);
		}

		// Update the CurrentGameTypeIdx value in gamestate. This will also trigger changes in the UI of the other players
		AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer()));
		if(GameStateLobby)
		{
			GameStateLobby->Server_SetCurrentGameType(resultGameType);
			GameStateLobby->Server_SetCurrentLevel(resultLevel);// Also reset level idx to zero, because every gametype will show its own list of available levels
		}
	}
}

void ULobbyMenu::ChangeLevel(int32 direction)
{
	const UDataTable* DatatableGameType = GameTypeDatatable.LoadSynchronous();
	
	if(IsValid(DatatableGameType))
	{
		// Get all the row values
		FLobbyGameTypeData* rowGameType = DatatableGameType->FindRow<FLobbyGameTypeData>(GetCurrentGameType().Second, TEXT("ULobbyMenu::ChangeLevel"));
		if(rowGameType)
		{
			// Make sure the level selection loops over the options (gametype struct has a an array of level names)
			const int newIdx = UOlmeHelperFunctions::ShiftInRotation(rowGameType->Maps.Num(), direction, GetCurrentLevel().First);
			const FName newName = rowGameType->Maps[newIdx];
			const FPairIntName resultLevel = {newIdx, newName};

			// Update the visual level info
			UpdateLevelInfo(resultLevel);

			// Update the currentlevel value in gamestate. This will also trigger changes in the UI of the other players
			AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer()));
			if(GameStateLobby)
			{
				GameStateLobby->Server_SetCurrentLevel(resultLevel);
			}
		}
	}
}

void ULobbyMenu::QuitLobby()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwningPlayer(), LevelAfterQuitLobby);
	UOnlineSessionFunctions::DestroySession(GetOwningPlayer());
}

void ULobbyMenu::StartGame()
{
	const UDataTable* Datatable = LevelDatatable.LoadSynchronous();
	
	if(!IsValid(Datatable))
	{
		return;
	}

	FLevelData* row = Datatable->FindRow<FLevelData>(GetCurrentLevel().Second, TEXT("ULobbyMenu::StartGame"));
	if(!row)
	{
		return;
	}
	
	if(APlayerControllerLobby* pc = Cast<APlayerControllerLobby>(GetOwningPlayer()))
	{
		pc->StartGame(row->FileName.ToString());
	}
}

FPairIntName ULobbyMenu::GetCurrentLevel() const
{
	if(const AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer())))
	{
		return GameStateLobby->GetCurrentLevel();
	}

	return FPairIntName{-1, TEXT("")};
}

FPairIntName ULobbyMenu::GetCurrentGameType() const
{
	if(const AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer())))
	{
		return GameStateLobby->GetCurrentGameType();
	}

	return {-1, TEXT("")};
}
