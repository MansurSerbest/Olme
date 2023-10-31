// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/HUDLobby.h"

#include "UISystemFunctions.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/Lobby/UI/LobbyMenu.h"

void AHUDLobby::TryCreateLobbyMenu()
{
	ULobbyMenu* Widget = Cast<ULobbyMenu>(UUISystemFunctions::GetActiveWidget(this));
	if(!Widget)
	{
		Widget = CreateWidget<ULobbyMenu>(GetOwningPlayerController(), MainWidgetClass);
		UUISystemFunctions::PushWidgetFromInstance(this, Widget);
		if(Widget)
		{
			const bool bIsHost = GetNetMode() == (NM_ListenServer);
			Widget->Init(bIsHost);
		}
	}
}

void AHUDLobby::BeginPlay()
{
	Super::BeginPlay();

	TryCreateLobbyMenu();
}


