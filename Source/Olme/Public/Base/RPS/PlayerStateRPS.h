// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/TurnBased/PlayerStateTurnBased.h"
#include "PlayerStateRPS.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerStateRPS : public APlayerStateTurnBased
{
	GENERATED_BODY()

public:
	APlayerStateRPS();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnRep_Score() override;

	UFUNCTION(Server, Reliable)
	void ToggleIsReady_Server();

	void SetupStartMatch();

	bool GetIsReady() const {return bIsReady;}

	void SetIsReady(const bool Value) {bIsReady = Value;}
	
protected:
	virtual void OnRep_CustomName() override;

	UFUNCTION()
	void OnRep_IsReady();

private:
	UPROPERTY(ReplicatedUsing = OnRep_IsReady)
	bool bIsReady = false;
};
