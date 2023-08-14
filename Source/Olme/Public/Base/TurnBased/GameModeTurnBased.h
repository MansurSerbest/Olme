// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeTurnBased.generated.h"

class UGameTypeBase;

/**
 * 
 */
UCLASS()
class OLME_API AGameModeTurnBased : public AGameMode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UGameTypeBase* GameType;
};
