// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateTurnBased.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerStateTurnBased : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_Name();

	UFUNCTION(Server, Reliable)
	void SetName_Server(const FString& NewName);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Name)
	FString Name;
};
