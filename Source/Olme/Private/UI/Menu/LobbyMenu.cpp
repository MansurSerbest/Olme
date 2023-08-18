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

void ULobbyMenu::UpdatePlayerList(const TArray<FLobbyPlayerData>& PlayerData, const int32 CurrNrOfPlayers)
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

	// Update the number of players data
	if(AGameStateLobby* gs = AGameStateLobby::GetInstance(GetOwningPlayer()))
	{
		UpdatePlayerNumberInfo(CurrNrOfPlayers, gs->GetMaxNumberOfPlayers());
	}
}

void ULobbyMenu::Init(const bool isHost)
{
	bIsHost = isHost;
	if(!bIsHost)
	{
		ChooseLevelButtonLeft->SetVisibility(ESlateVisibility::Collapsed);
		ChooseLevelButtonRight->SetVisibility(ESlateVisibility::Collapsed);
		ChooseGameTypeButtonLeft->SetVisibility(ESlateVisibility::Collapsed);
		ChooseGameTypeButtonRight->SetVisibility(ESlateVisibility::Collapsed);
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

void ULobbyMenu::UpdatePlayerNumberInfo(const int32 CurrNumberOfPlayers, const int32 MaxNumberOfPlayers)
{
	const FText newFormat = FText::Format(FText::FromString(TEXT("{0}/{1}")), FText::AsNumber(CurrNumberOfPlayers), FText::AsNumber(MaxNumberOfPlayers));
	NrOfPlayersText->SetText(newFormat);
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
	// ChangeGameType(0);
	// ChangeLevel(0);
}

void ULobbyMenu::ChangeLevelLeft()
{
	// Update the currentlevel value in gamestate. This will also trigger changes in the UI of the other players
	if(AGameStateLobby* GameStateLobby = AGameStateLobby::GetInstance(GetOwningPlayer()))
	{
		GameStateLobby->Server_ChangeLevel(-1);
	}
}

void ULobbyMenu::ChangeLevelRight()
{
	// Update the currentlevel value in gamestate. This will also trigger changes in the UI of the other players
	if(AGameStateLobby* GameStateLobby = AGameStateLobby::GetInstance(GetOwningPlayer()))
	{
		GameStateLobby->Server_ChangeLevel(1);
	}
}

void ULobbyMenu::ChangeGameTypeLeft()
{
	// Update the CurrentGameTypeIdx value in gamestate. This will also trigger changes in the UI of the other players
	AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer()));
	if(GameStateLobby)
	{
		GameStateLobby->Server_ChangeGameType(-1);
	}
}

void ULobbyMenu::ChangeGameTypeRight()
{
	// Update the CurrentGameTypeIdx value in gamestate. This will also trigger changes in the UI of the other players
	AGameStateLobby* GameStateLobby = Cast<AGameStateLobby>(UGameplayStatics::GetGameState(GetOwningPlayer()));
	if(GameStateLobby)
	{
		GameStateLobby->Server_ChangeGameType(1);
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
	if(const AGameStateLobby* GameStateLobby = AGameStateLobby::GetInstance(GetOwningPlayer()))
	{
		return GameStateLobby->GetCurrentLevel();
	}

	return FPairIntName{-1, TEXT("")};
}

FPairIntName ULobbyMenu::GetCurrentGameType() const
{
	if(const AGameStateLobby* GameStateLobby = AGameStateLobby::GetInstance(GetOwningPlayer()))
	{
		return GameStateLobby->GetCurrentGameType();
	}

	return {-1, TEXT("")};
}
