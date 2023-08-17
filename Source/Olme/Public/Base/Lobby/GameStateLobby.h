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

public:
	UFUNCTION()
	void OnRep_CurrentLevel();

	UFUNCTION(Server, Reliable)
	void Server_SetCurrentLevel(const FPairIntName& Pair);

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnRep_GameType();

	UFUNCTION(Server, Reliable)
	void Server_SetCurrentGameType(const FPairIntName& Pair);

	FPairIntName GetCurrentLevel() const;

	FPairIntName GetCurrentGameType() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> DataTableGameType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> DataTableLevel;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentLevel)
	FPairIntName CurrentLevel;

	UPROPERTY(ReplicatedUsing = OnRep_GameType)
	FPairIntName CurrentGameType;
};
