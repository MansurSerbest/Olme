// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/GameStateRPS.h"

#include "UISystemFunctions.h"
#include "Base/RPS/PlayerStateRPS.h"
#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"
#include "Gameplay/RockPaperScissors/UI/WidgetRPS.h"
#include "Net/UnrealNetwork.h"

void AGameStateRPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameStateRPS, TimeRemaining);
	DOREPLIFETIME(AGameStateRPS, Round);
	DOREPLIFETIME(AGameStateRPS, bMatchStarted);
}

AGameStateRPS::AGameStateRPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
}

void AGameStateRPS::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	if(GetNetMode() == NM_ListenServer)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameStateRPS::OnTimerFinished, StartTime);
	}
}

void AGameStateRPS::TryStartRound()
{
	// Count how many players have pressed ready
	int32 count = 0;
	TArray<APlayerStateRPS*> PlayerStatesRPS;
	for(APlayerState* PlayerState : PlayerArray)
	{
		// Check if every player has pressed ready
		if(APlayerStateRPS* PS = Cast<APlayerStateRPS>(PlayerState))
		{
			if(PS->GetIsReady())
			{
				++count;
				PlayerStatesRPS.Add(PS);
			}
		}
	}
	
	// If every players has pressed ready, start next round
	if(count == 2)
	{
		// Increment Round
		Round++;
			
		// Start Timer again
		GetWorldTimerManager().ClearTimer(TimerHandle);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameStateRPS::OnTimerFinished, StartTime);

		// Set Players to start state;
		for(APlayerStateRPS* PS : PlayerStatesRPS)
		{
			//Set the icons to rps and questions mark
			if(ACharacterRPS* Character = Cast<ACharacterRPS>(PS->GetPawn()))
			{
				Character->StartRound();
			}

			// Set ready to false
			PS->SetIsReady(false);
		}

		bMatchStarted = true;
		OnRep_MatchStarted();
	}
}

void AGameStateRPS::OnRep_MatchStarted()
{
	// Update UI
	if(UWidgetRPS* Widget = Cast<UWidgetRPS>(UUISystemFunctions::GetActiveWidget(this)))
	{
		Widget->SetResultTextVisibility(!bMatchStarted);
		Widget->SetRound(Round);
	}
}

void AGameStateRPS::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetNetMode() == NM_ListenServer)
	{
		TimeRemaining = FMath::Clamp(GetWorldTimerManager().GetTimerRemaining(TimerHandle), 0.0f, StartTime);
	}

	if(UWidgetRPS* Widget = Cast<UWidgetRPS>(UUISystemFunctions::GetActiveWidget(this)))
	{
		Widget->SetTime(TimeRemaining);
	}
}

void AGameStateRPS::OnTimerFinished()
{
	bMatchStarted = false;
	
	ResolveMatchResult();
}

void AGameStateRPS::ResolveMatchResult()
{
	// Make sure there are 2 players
	if(PlayerArray.Num() == 2)
	{
		//Get the characters and compare their choices and determine the winner
		ACharacterRPS* PlayerOne = Cast<ACharacterRPS>(PlayerArray[0]->GetPawn());
		ACharacterRPS* PlayerTwo = Cast<ACharacterRPS>(PlayerArray[1]->GetPawn());
		ACharacterRPS* Winner = ACharacterRPS::ResolveWinner(PlayerOne, PlayerTwo);
		
		if(!Winner)
		{
			OnMatchFinished(PlayerOne, PlayerTwo, TEXT("Draw"));
		}
		else if(APlayerStateRPS* PS = Cast<APlayerStateRPS>(Winner->GetPlayerState()))
		{
			PS->SetScore(PS->GetScore() + 1);
			PS->OnRep_Score();

			// Broadcast the result to the listen server and all the clients
			OnMatchFinished(PlayerOne, PlayerTwo, Winner? PS->GetCustomName() : TEXT("Draw"));
		}
	}
}

void AGameStateRPS::OnMatchFinished_Implementation(ACharacterRPS* PlayerOne, ACharacterRPS* PlayerTwo, const FString& Result)
{
	// Get the expected widget first and Update the widget result text
	if(UWidgetRPS* Widget = Cast<UWidgetRPS>(UUISystemFunctions::GetActiveWidget(this)))
	{
		Widget->SetResultText(true,  Result);
	}
	
	// Show the 'ready' checkboxes for the players
	PlayerOne->SetCheckBoxes(false);
	PlayerTwo->SetCheckBoxes(false);
}
