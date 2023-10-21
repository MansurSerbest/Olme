// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/RockPaperScissors/RPSStructs.h"
#include "WidgetRPSCharacter.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class OLME_API UWidgetRPSCharacter : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* PlayerName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* LeftArrow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* RightArrow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Choice;

	UPROPERTY(EditDefaultsOnly, Category = "Textures")
	TMap<ERockPaperScissors, TSoftObjectPtr<UTexture2D>> RPSTextures;
};
