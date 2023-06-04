// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Lobby/HUDLobby.h"

#include "UISystemBPLibrary.h"
#include "Blueprint/UserWidget.h"

void AHUDLobby::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);
	UUISystemBPLibrary::PushWidgetFromInstance(this, Widget);
}
