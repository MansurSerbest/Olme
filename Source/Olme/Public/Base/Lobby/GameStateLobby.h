// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Structs/OlmeStructs.h"
#include "GameStateLobby.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API AGameStateLobby : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	static AGameStateLobby* GetInstance(const UObject* WorldContextObject);

	// Level Logic
	UFUNCTION()
	void OnRep_CurrentLevel();

	UFUNCTION(Server, Reliable)
	void Server_ChangeLevel(const int32 Direction);

	// GameType logic
	UFUNCTION()
	void OnRep_CurrentGameType();

	UFUNCTION(Server, Reliable)
	void Server_ChangeGameType(const int32 Direction);

	FPairIntName GetCurrentLevel() const;

	FPairIntName GetCurrentGameType() const;

	// Num of players logic
	UFUNCTION()
	void OnRep_MaxNumberOfPlayers();

	int32 GetMaxNumberOfPlayers() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> DataTableGameType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> DataTableLevel;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentLevel)
	FPairIntName CurrentLevel;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentGameType)
	FPairIntName CurrentGameType;
	
	UPROPERTY(Replicated)
	int32 MinNumberOfPlayers;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxNumberOfPlayers)
	int32 MaxNumberOfPlayers;

	
};
