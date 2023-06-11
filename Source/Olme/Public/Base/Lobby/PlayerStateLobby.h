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
	APlayerStateLobby();
	
	virtual FString GetPlayerNameCustom() const override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnRep_NameCustom();
private:
	UPROPERTY(ReplicatedUsing = OnRep_NameCustom)
	FString NameCustom;
};
