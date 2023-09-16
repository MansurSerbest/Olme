// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"
#include "LoginMenu.generated.h"


class UButton;
class UEditableText;
/**
 * 
 */
UCLASS()
class OLME_API ULoginMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void LoginPlayfabAccount();

	UFUNCTION()
	void LoginEpicGamesAcount();

	UFUNCTION()
	void RegisterAccount();

	void OnLoginCompletedPlayfab(bool Result);

	void StartLogin();

	void FinishLogin();

	void OnLoginCompletedEpicGames(bool Result);

#if WITH_EDITOR
	void AutoLoginWithPlayfab();

	void AutoLoginWithEpicGames();
#endif
	
protected:
	// Login via Playfab
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LoginButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RegisterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UsernamePrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* PasswordPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RetryText;

	// Login Via Epic Games
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LoginEpicGamesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* LoginInThrobber;

	UPROPERTY(EditDefaultsOnly, Category = DefaultClasses)
	TSubclassOf<UUserWidget> RegisterAccountWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = DefaultClasses)
	TSoftObjectPtr<UWorld> MainMenuLevel;

private:
	FDelegateHandle OnLoginFinishedPlayfabDelegateHandle;
	FDelegateHandle OnLoginFinishedEpicGamesDelegateHandle;
};
