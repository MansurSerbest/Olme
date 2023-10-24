// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay\RockPaperScissors\UI\WidgetRPSCharacter.h"

#include "Components/Image.h"

void UWidgetRPSCharacter::SetChoice(const ERockPaperScissors NewChoice)
{
	if(Choice)
	{
		Choice->SetBrushFromTexture(RPSTextures[NewChoice]);
	}
}

void UWidgetRPSCharacter::NativeConstruct()
{
	Super::NativeConstruct();
}
