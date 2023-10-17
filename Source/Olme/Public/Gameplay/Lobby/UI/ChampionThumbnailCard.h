// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ChampionThumbnailCard.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UChampionThumbnailCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(UTexture2D* ThumbnailTexture, const FText& ChampionNameText);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ChampionThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ChampionName;
};
