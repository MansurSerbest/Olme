// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/HUDLobby.h"

#include "UISystemFunctions.h"
#include "Base/Lobby/PlayerControllerLobby.h"
#include "Blueprint/UserWidget.h"

void AHUDLobby::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);
	UUISystemFunctions::PushWidgetFromInstance(this, Widget);

	if(APlayerControllerLobby* PC = Cast<APlayerControllerLobby>( GetOwningPlayerController()))
	{
		PC->OnHudBeginplayFinished();
	}
}
