// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerStateLobby : public APlayerState
{
	GENERATED_BODY()

public:
	virtual FString GetPlayerNameCustom() const override;
};
