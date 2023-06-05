// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LobbyMenu.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/ChampionThumbnailCard.h"

ULobbyMenu::ULobbyMenu(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
, NrOfColumsChampionsGrid{4}
, CurrentLevelIdx{0}
{
}

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	FillChampionsGrid();
	ChangeLevel(0);

	ChooseLevelButtonLeft->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelLeft);
	ChooseLevelButtonRight->OnPressed.AddDynamic(this, &ULobbyMenu::ChangeLevelRight);
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
