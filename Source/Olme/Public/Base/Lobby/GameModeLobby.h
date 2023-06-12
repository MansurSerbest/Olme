// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeLobby.generated.h"

class APlayerControllerLobby;
/**
 * 
 */
UCLASS()
class OLME_API AGameModeLobby : public AGameMode
{
	GENERATED_BODY()

public:
	void UpdatePlayerList() const;
protected:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

private:
	UPROPERTY()
	TArray<APlayerControllerLobby*> LoggedInPlayerControllers;
};
