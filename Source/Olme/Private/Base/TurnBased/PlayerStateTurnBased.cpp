// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/TurnBased/PlayerStateTurnBased.h"

#include "AccountManagerFunctions.h"
#include "GameFramework/GameState.h"
#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Olme/Olme.h"

void APlayerStateTurnBased::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateTurnBased, Name);
}

void APlayerStateTurnBased::BeginPlay()
{
	Super::BeginPlay();

	// Don't trigger the logic below if the match has ended. This beginplay can be triggered when destroying a playerstate and creating a new one to put it in the inactive
	// playerstate array
	const AGameState* GameState = Cast<AGameState>( UGameplayStatics::GetGameState(this));
	if(GameState && GameState->HasMatchEnded())
	{
		return;
	}

	// Get the name and call a function only on server
	Name = UAccountManagerFunctions::GetCachedUsername(this);
	SetName_Server(Name);
}

void APlayerStateTurnBased::OnRep_Name()
{
	ACharacterRPS* Pawn = Cast<ACharacterRPS>(GetPawn());
	if(Pawn)
	{
		UE_LOG(LogOlme, Log, TEXT("Name of %s is %s"), *GetName(), *Name);
	}
}

void APlayerStateTurnBased::SetName_Server_Implementation(const FString& NewName)
{
	Name = NewName;
	OnRep_Name();
}
