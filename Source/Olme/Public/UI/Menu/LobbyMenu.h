// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyPlayerEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
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

	void Init(const bool isHost);

	void UpdateLevelInfo(const FPairIntName& Pair);

	void UpdateGameTypeInfo(const FPairIntName& Pair);
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ChangeLevelLeft();

	UFUNCTION()
	void ChangeLevelRight();

	UFUNCTION()
	void ChangeGameTypeLeft();

	UFUNCTION()
	void ChangeGameTypeRight();

	void ChangeGameType(int32 direction);

	void ChangeLevel(int32 direction);

	UFUNCTION()
	void QuitLobby();

	UFUNCTION()
	void StartGame();

	FPairIntName GetCurrentLevel() const;

	FPairIntName GetCurrentGameType() const;

protected:
	// Player List
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* PlayerInfoList;
	
	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSubclassOf<ULobbyPlayerEntry> PlayerInfoEntryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NrOfPlayersText;

	// Game Type Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseGameTypeButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseGameTypeButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GameTypeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> GameTypeDatatable;
	
	// Level Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseLevelButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChooseLevelButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* LevelThumbnail;

	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UDataTable> LevelDatatable;

	// Start-Quit 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitLobbyButton;
	
	// Level that should open after quitting the lobby
	UPROPERTY(EditAnywhere, Category = LobbyDefaults)
	TSoftObjectPtr<UWorld> LevelAfterQuitLobby;

private:
	bool bIsHost{false};
};
