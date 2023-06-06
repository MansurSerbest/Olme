// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/HUDMainMenu.h"

#include "UISystemBPLibrary.h"
#include "UIWorldSubsystem.h"

void AHUDMainMenu::BeginPlay()
{
	Super::BeginPlay();

	UUISystemBPLibrary::PushWidgetFromClass(this, BaseWidgetClass);
}
