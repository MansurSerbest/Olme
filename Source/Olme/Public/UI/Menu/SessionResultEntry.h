// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SessionResultEntry.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API USessionResultEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void Init(const FOnlineSessionSearchResult& Result);
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* JoinBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SessionNameText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerNumberText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PingText;

	FOnlineSessionSearchResult SessionResult;
private:
	UFUNCTION()
	void JoinSession();

	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
};
