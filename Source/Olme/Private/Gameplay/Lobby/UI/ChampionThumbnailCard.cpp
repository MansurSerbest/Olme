// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Lobby/UI/ChampionThumbnailCard.h"

void UChampionThumbnailCard::Setup(UTexture2D* ThumbnailTexture, const FText& ChampionNameText)
{
	ChampionThumbnail->SetBrushFromTexture(ThumbnailTexture);
	ChampionName->SetText(ChampionNameText); 
}

void UChampionThumbnailCard::NativeConstruct()
{
	Super::NativeConstruct();
}
