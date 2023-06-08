// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerStateLobby.h"

#include "AccountManagerFunctions.h"

FString APlayerStateLobby::GetPlayerNameCustom() const
{
	return UAccountManagerFunctions::GetPlayfabId(this);
}
