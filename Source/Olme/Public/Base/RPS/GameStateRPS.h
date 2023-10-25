// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/TurnBased/GameStateTurnBased.h"
#include "GameStateRPS.generated.h"

class APlayerStateRPS;
/**
 * 
 */
UCLASS()
class OLME_API AGameStateRPS : public AGameStateTurnBased
{
	GENERATED_BODY()

public:
	AGameStateRPS();

	void TryStartRound();

	bool GetMatchStarted() const {return bMatchStarted;}
	
protected:
	virtual void HandleMatchHasStarted() override;

private:
	void OnTimerFinished();
	
	void ResolveMatchResult();

	UFUNCTION(NetMulticast, Reliable)
	void OnMatchFinished(ACharacterRPS* PlayerOne, ACharacterRPS* PlayerTwo, const FString& Result);

	UFUNCTION()
	void OnRep_MatchStarted();

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	FTimerHandle TimerHandle;

	float StartTime = 10.0f;
	
	UPROPERTY(Replicated)
	float TimeRemaining = StartTime;

	UPROPERTY(Replicated)
	int32 Round = 1;

	UPROPERTY(ReplicatedUsing = OnRep_MatchStarted)
	bool bMatchStarted = true;
};


