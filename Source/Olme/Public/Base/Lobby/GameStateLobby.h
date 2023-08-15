// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AGameStateLobby : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnRep_CurrentLevelIdx();

	UFUNCTION(Server, Reliable)
	void Server_SetCurrentLevelIdx(const int32 idx);
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentLevelIdx)
	int32 CurrentLevelIdx;
};
