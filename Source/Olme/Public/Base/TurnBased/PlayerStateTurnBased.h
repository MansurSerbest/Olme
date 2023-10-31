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

public:
	FString GetCustomName() const {return CustomName;}
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnRep_CustomName();

	UFUNCTION(Server, Reliable)
	void SetName_Server(const FString& NewName);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CustomName)
	FString CustomName;
};
