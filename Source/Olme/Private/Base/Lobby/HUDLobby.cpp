// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/HUDLobby.h"

#include "UISystemFunctions.h"
#include "Blueprint/UserWidget.h"
#include "UI/Menu/LobbyMenu.h"

void AHUDLobby::TryCreateLobbyMenu()
{
	UUserWidget* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(!Widget)
	{
		Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);
		UUISystemFunctions::PushWidgetFromInstance(this, Widget);
	}
}

void AHUDLobby::BeginPlay()
{
	Super::BeginPlay();

	TryCreateLobbyMenu();
}


