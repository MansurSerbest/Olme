// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerEntry.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class OLME_API ULobbyPlayerEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(const FText& Number, const FText& Name);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EntryNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerName;
};
