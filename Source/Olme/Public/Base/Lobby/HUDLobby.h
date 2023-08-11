// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AHUDLobby : public AHUD
{
	GENERATED_BODY()

public:
	void TryCreateLobbyMenu();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainWidgetClass;
};
