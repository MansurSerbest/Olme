// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "FindSessionMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UFindSessionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup();
	
protected:
	virtual void NativeConstruct() override;

private:
	void OnSessionFound(const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful) const;

	UFUNCTION()
	void FindSessions();
	
protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* ListOfSessions;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USessionResultEntry> SessionResultType;

private:
	FDelegateHandle FindSessionCompleteHandle;
};
