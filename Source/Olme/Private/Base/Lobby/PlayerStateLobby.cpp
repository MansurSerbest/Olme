// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/PlayerStateLobby.h"

FString APlayerStateLobby::GetPlayerNameCustom() const
{
	return BP_GetUniqueId().ToString();
}
