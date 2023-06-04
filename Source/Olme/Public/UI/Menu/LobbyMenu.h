// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/DataTable.h"
#include "LobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API ULobbyMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	void FillChampionsGrid();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* PlayerInfoList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseMapButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseMapButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* LevelThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* ChampionGridPanel;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSubclassOf<UUserWidget> PlayerInfoEntryClass;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSubclassOf<UUserWidget> ChampionCardClass;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UDataTable> MapsDatatable;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UDataTable> ChampionsDatatable;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	int32 NrOfColumsChampionsGrid;
};
