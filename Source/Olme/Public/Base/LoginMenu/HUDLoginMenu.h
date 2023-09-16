// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDLoginMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AHUDLoginMenu : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UUserWidget> BaseWidgetClass;
};
