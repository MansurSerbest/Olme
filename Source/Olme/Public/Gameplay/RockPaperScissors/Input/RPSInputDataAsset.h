// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RPSInputDataAsset.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class OLME_API URPSInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	URPSInputDataAsset(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Choose;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ConfirmChoice;
};
