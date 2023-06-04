// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnPressedSinglePlayerBtn();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenSinglePlayerMenu();

	UFUNCTION()
	void OnPressedOnlineMultiplayerBtn();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenOnlineMultiplayerMenu();

	UFUNCTION()
	void OnPressedSettingsBtn();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenSettingsMenu();

	UFUNCTION()
	void OnPressedExitBtn();
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SinglePlayerBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OnlineMultiplayerBtn;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SettingsBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitBtn;


};
