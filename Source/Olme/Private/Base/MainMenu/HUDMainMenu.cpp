// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MainMenu/HUDMainMenu.h"

#include "UISystemFunctions.h"

void AHUDMainMenu::BeginPlay()
{
	Super::BeginPlay();

	UUISystemFunctions::PushWidgetFromClass(this, BaseWidgetClass);
}
