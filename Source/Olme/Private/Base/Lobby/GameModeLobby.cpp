// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameModeLobby.h"

#include "Base/Lobby/PlayerControllerLobby.h"
#include "Olme/Olme.h"

void AGameModeLobby::OnPostLogin(AController* NewPlayer)
{
	UE_LOG(LogOlme, Log, TEXT("Postlogin! Player: %s"), *NewPlayer->GetName());
}

void AGameModeLobby::StartGame(const FString& level)
{
	if(UWorld* World = GetWorld())
	{
		World->ServerTravel(level);
	}
}

void AGameModeLobby::BeginPlay()
{
	Super::BeginPlay();

	// Remove the cached playercontroller if they logout
	FGameModeEvents::GameModeLogoutEvent.AddLambda([this](AGameModeBase* GameMode, AController* PlayerController)->void
	{
		LoggedInPlayerControllers.Remove(Cast<APlayerControllerLobby>(PlayerController));
	});
}
