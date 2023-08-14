// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LobbyMenu.h"

#include "OnlineSessionFunctions.h"
#include "Base/Lobby/GameStateLobby.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/ChampionThumbnailCard.h"

ULobbyMenu::ULobbyMenu(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
, NrOfColumsChampionsGrid{4}
, CurrentLevelIdx{0}
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

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Assign button logic
	ChooseLevelButtonLeft->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelLeft);
	ChooseLevelButtonRight->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelRight);
	QuitLobbyButton->OnPressed.AddDynamic(this, &ULobbyMenu::QuitLobby);
	StartGameButton->OnPressed.AddDynamic(this, &ULobbyMenu::StartGame);

	// Fill in champion grid
	FillChampionsGrid();
	// Change level logic
	ChangeLevel(0);
}


void ULobbyMenu::FillChampionsGrid()
{
    const UDataTable* Datatable = ChampionsDatatable.LoadSynchronous();

    if(IsValid(Datatable))
    {
    	int32 ItCounter = 0;
    	Datatable->ForeachRow<FChampionData>(FString(TEXT("ULobbyMenu::FillChampionsGrid")),
    		[this, &ItCounter](const FName& Key, const FChampionData& Value)->void
    	{
    			UChampionThumbnailCard* ChampionCardWidget =
    				CreateWidget<UChampionThumbnailCard>(GetOwningPlayer(), ChampionCardClass);
    		   if(IsValid(ChampionCardWidget))
    		   {
    			   ChampionCardWidget->Setup(Value.Thumbnail, Value.DisplayName);
    			   ChampionGridPanel->AddChildToGrid(ChampionCardWidget, ItCounter / NrOfColumsChampionsGrid, ItCounter % NrOfColumsChampionsGrid);
    			   ++ItCounter;
    		   }
    	});
    }
}

void ULobbyMenu::ChangeLevelLeft()
{
	ChangeLevel(-1);
}

void ULobbyMenu::ChangeLevelRight()
{
	ChangeLevel(1);
}

void ULobbyMenu::ChangeLevel(int32 direction)
{
	const UDataTable* Datatable = LevelDatatable.LoadSynchronous();
	
	if(IsValid(Datatable))
	{
		TArray<FLevelData*> LevelDataArr;
		Datatable->GetAllRows(FString(TEXT("ULobbyMenu::ChangeLevel(int32 direction)")), LevelDataArr);

		// Make sure the level selection loops over the options
		CurrentLevelIdx += direction;
		if(CurrentLevelIdx < 0)
		{
			CurrentLevelIdx = LevelDataArr.Num() -1;
		}
		else if(CurrentLevelIdx > LevelDataArr.Num() - 1)
		{
			CurrentLevelIdx = 0;
		}
		
		if(LevelDataArr.IsValidIndex(CurrentLevelIdx))
		{
			LevelName->SetText(LevelDataArr[CurrentLevelIdx]->DisplayName);
			LevelThumbnail->SetBrushFromTexture(LevelDataArr[CurrentLevelIdx]->Thumbnail);
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
	
	if(IsValid(Datatable))
	{
		TArray<FLevelData*> LevelDataArr;
		Datatable->GetAllRows(FString(TEXT("ULobbyMenu::StartGame()")), LevelDataArr);

		if(LevelDataArr.IsValidIndex(CurrentLevelIdx))
		{
			APlayerControllerLobby* pc = Cast<APlayerControllerLobby>(GetOwningPlayer());
			if(pc)
			{
				pc->StartGame(LevelDataArr[CurrentLevelIdx]->FileName.ToString());
			}
		}
	}
}
