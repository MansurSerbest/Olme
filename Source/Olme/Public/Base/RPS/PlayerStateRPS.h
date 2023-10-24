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

protected:
	virtual void OnRep_CustomName() override;
};
