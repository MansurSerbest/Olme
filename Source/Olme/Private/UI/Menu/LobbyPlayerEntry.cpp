// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LobbyPlayerEntry.h"
#include "Components/TextBlock.h"

void ULobbyPlayerEntry::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULobbyPlayerEntry::Setup(const FText& Number, const FText& Name)
{
	EntryNumber->SetText(Number);
	PlayerName->SetText(Name);
}
