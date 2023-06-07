// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChampionThumbnailCard.h"
#include "LobbyPlayerEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/DataTable.h"
#include "Structs/OlmeStructs.h"
#include "LobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API ULobbyMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	ULobbyMenu(const FObjectInitializer& ObjectInitializer);

	void UpdatePlayerList(const TArray<FLobbyPlayerData>& PlayerData);
	
protected:
	virtual void NativeConstruct() override;

private:
	void FillChampionsGrid();

	UFUNCTION()
	void ChangeLevelLeft();

	UFUNCTION()
	void ChangeLevelRight();

	void ChangeLevel(int32 direction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* PlayerInfoList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseLevelButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseLevelButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* LevelThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* ChampionGridPanel;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSubclassOf<ULobbyPlayerEntry> PlayerInfoEntryClass;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSubclassOf<UChampionThumbnailCard> ChampionCardClass;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UDataTable> LevelDatatable;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UDataTable> ChampionsDatatable;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	int32 NrOfColumsChampionsGrid;

private:
	int32 CurrentLevelIdx;
};
