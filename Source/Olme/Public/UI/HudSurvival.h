// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudSurvival.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AHudSurvival : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainWidgetClass;
	
	
};
