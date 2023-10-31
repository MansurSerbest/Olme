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

public:
	void SetChoice(const ERockPaperScissors NewChoice);

	void SetName(const FString& NewName);

	void SetScore(const float NewScore);

	void SetCheckbox(const bool bMarked);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Score;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LeftArrow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> RightArrow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MainImage;

	UPROPERTY(EditDefaultsOnly, Category = "Textures")
	TMap<ERockPaperScissors, TObjectPtr<UTexture2D>> RPSTextures;

	UPROPERTY(EditDefaultsOnly, Category = "Textures")
	TObjectPtr<UTexture2D> CheckBoxMarked;

	UPROPERTY(EditDefaultsOnly, Category = "Textures")
	TObjectPtr<UTexture2D> CheckBoxUnmarked;
};
