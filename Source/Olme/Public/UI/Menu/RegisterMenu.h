// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RegisterMenu.generated.h"


class UEditableText;
class UButton;
class UCircularThrobber;
class UTextBlock;
/**
 * 
 */
UCLASS()
class OLME_API URegisterMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void RegisterPlayfabAccount();

	UFUNCTION()
	void Back();

	void OnRegisterFinished(bool Result);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RegisterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EmailPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UsernamePrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* PasswordPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RetryText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCircularThrobber* RegisteringThrobber;

	UPROPERTY(EditDefaultsOnly, Category = DefaultClasses)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = DefaultClasses)
	TSubclassOf<UUserWidget> LoginWidgetClass;

private:
	FDelegateHandle OnRegisterFinishedDelegateHandle;
};
