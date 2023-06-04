// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "OnlineMultiplayerMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UOnlineMultiplayerMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnHostSessionPressed();

	UFUNCTION()
	void OnFindSessionPressed();

	UFUNCTION()
	void OnOptionsPressed();

	UFUNCTION()
	void OnBackPressed();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostSessionBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* FindSessionBtn;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
};
