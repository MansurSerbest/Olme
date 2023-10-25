// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RockPaperScissors/UI/WidgetRPS.h"
#include "UMG/Public/Components/TextBlock.h"

void UWidgetRPS::NativeConstruct()
{
	Super::NativeConstruct();

	ResultText->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetRPS::SetTime(const float NewTime)
{
	const FText TimeText = FText::Format(FText::FromString(TEXT("{0}")),{NewTime});
	Time->SetText(TimeText);
}

void UWidgetRPS::SetResultText(const bool bStart, const FString& Text)
{
	if(bStart)
	{
		ResultText->SetVisibility(ESlateVisibility::HitTestInvisible);
		const FText TempText = FText::Format(FText::FromString("Winner : {0}"), FText::FromString(Text));
		ResultText->SetText(TempText);
	}
	else
	{
		ResultText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWidgetRPS::SetResultTextVisibility(const bool Value)
{
	Value? ResultText->SetVisibility(ESlateVisibility::HitTestInvisible) : ResultText->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidgetRPS::SetRound(const int32 Value)
{
	RoundNr->SetText(FText::Format(FText::FromString(TEXT("{0}")), Value));
}
