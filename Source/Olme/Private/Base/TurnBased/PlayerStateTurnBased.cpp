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

	DOREPLIFETIME(APlayerStateTurnBased, CustomName);
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

	// Set the name and call it properly in server if necessary
	const ENetMode NM = GetNetMode();
	if(NM == NM_Client)
	{
		if(GetPlayerController() && GetPlayerController()->IsLocalController())
		{
			CustomName = UAccountManagerFunctions::GetCachedUsername(this);
			OnRep_CustomName();
			SetName_Server(CustomName); // We need to update the name in the server too
		}
	}
	else if(NM == NM_ListenServer)
	{
		if(GetPlayerController() && GetPlayerController()->IsLocalController())
		{
			CustomName = UAccountManagerFunctions::GetCachedUsername(this);
			OnRep_CustomName();
		}
	}
}

void APlayerStateTurnBased::OnRep_CustomName()
{
}

void APlayerStateTurnBased::SetName_Server_Implementation(const FString& NewName)
{
	CustomName = NewName;
	OnRep_CustomName(); // Call this because OnRep is only called in client
}
