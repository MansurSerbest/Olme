// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "HostSessionMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UHostSessionMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnPressedHostSessionBtn();

	UFUNCTION()
	void OnCreateSession(bool Success);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* HostSessionBtn;

private:
	FDelegateHandle OnCreateSessionCompleteHandle;
};
