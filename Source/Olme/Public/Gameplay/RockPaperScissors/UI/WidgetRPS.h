// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetRPS.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class OLME_API UWidgetRPS : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetTime(const float NewTime);

	void SetResultText(const bool bStart, const FString& Text = TEXT(""));

	void SetResultTextVisibility(const bool Value);

	void SetRound(const int32 Value);
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RoundNr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText;
};
