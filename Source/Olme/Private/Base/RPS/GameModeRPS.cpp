// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/GameModeRPS.h"

#include "Base/RPS/PlayerControllerRPS.h"
#include "Olme/Olme.h"


AGameModeRPS::AGameModeRPS()
	:MaxNrOfPlayers{2}
{
}

void AGameModeRPS::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	// All the player that are loging in after the game is full need to be kicked out
	if(LoggedInPlayerControllers.Num() < MaxNrOfPlayers)
	{
		LoggedInPlayerControllers.Add(Cast<APlayerControllerRPS>(NewPlayer));
		UE_LOG(LogOlme, Log, TEXT("AGameModeRPS::OnPostLogin: Logged in player %s"), *NewPlayer->GetName());
	}
	else if(LoggedInPlayerControllers.Num() >= MaxNrOfPlayers)
	{
		if(APlayerControllerRPS* PC = Cast<APlayerControllerRPS>(NewPlayer))
		{
			UE_LOG(LogOlme, Warning, TEXT("AGameModeRPS::OnPostLogin: Game is already full! Kicking out!"));
			PC->LeaveGame();
		}
	}
}
