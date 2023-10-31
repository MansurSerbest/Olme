// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/TurnBased/HUDTurnBased.h"
#include "HUDTurnRPS.generated.h"

class UWidgetRPS;
/**
 * 
 */
UCLASS()
class OLME_API AHUDTurnRPS : public AHUDTurnBased
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWidgetRPS> MainWidgetClass;
};
