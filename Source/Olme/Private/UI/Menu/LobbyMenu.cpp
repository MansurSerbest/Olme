// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LobbyMenu.h"
#include "Structs/OlmeStructs.h"
#include "UI/Menu/ChampionThumbnailCard.h"

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	NrOfColumsChampionsGrid = 4;

	FillChampionsGrid();
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
