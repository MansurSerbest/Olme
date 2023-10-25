// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay\RockPaperScissors\UI\WidgetRPSCharacter.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidgetRPSCharacter::SetChoice(const ERockPaperScissors NewChoice)
{
	if(MainImage)
	{
		MainImage->SetBrushFromTexture(RPSTextures[NewChoice]);
	}
}

void UWidgetRPSCharacter::SetName(const FString& NewName)
{
	if(PlayerName)
	{
		PlayerName->SetText(FText::FromString(NewName));
	}
}

void UWidgetRPSCharacter::SetScore(const float NewScore)
{
	if(Score)
	{
		Score->SetText(FText::Format(FText::FromString("{0}"), NewScore));
	}
}

void UWidgetRPSCharacter::SetCheckbox(const bool bMarked)
{
	if(MainImage)
	{
		bMarked? MainImage->SetBrushFromTexture(CheckBoxMarked) : MainImage->SetBrushFromTexture(CheckBoxUnmarked);
	}
}

void UWidgetRPSCharacter::NativeConstruct()
{
	Super::NativeConstruct();
}
