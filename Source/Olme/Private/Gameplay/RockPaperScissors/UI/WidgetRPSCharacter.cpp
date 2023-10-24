// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay\RockPaperScissors\UI\WidgetRPSCharacter.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidgetRPSCharacter::SetChoice(const ERockPaperScissors NewChoice)
{
	if(Choice)
	{
		Choice->SetBrushFromTexture(RPSTextures[NewChoice]);
	}
}

void UWidgetRPSCharacter::SetName(const FString& NewName)
{
	if(PlayerName)
	{
		PlayerName->SetText(FText::FromString(NewName));
	}
}

void UWidgetRPSCharacter::NativeConstruct()
{
	Super::NativeConstruct();
}
