// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/GameModeLobby.h"

void AGameModeLobby::OnPostLogin(AController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Postlogin! Player: %s"), *NewPlayer->GetName());
}
