// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceOlme.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UGameInstanceOlme : public UGameInstance
{
	GENERATED_BODY()

public:
	const TSoftObjectPtr<UWorld>& GetMainMenuMap() const {return MainMenuMap;}

	const TSoftObjectPtr<UWorld>& GetLobbyMap() const {return LobbyMap;}
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Maps")
	TSoftObjectPtr<UWorld> MainMenuMap;

	UPROPERTY(EditDefaultsOnly, Category = "Maps")
	TSoftObjectPtr<UWorld> LobbyMap;
};
