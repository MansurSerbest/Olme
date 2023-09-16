// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/LoginMenu/HUDLoginMenu.h"

#include "UISystemFunctions.h"

void AHUDLoginMenu::BeginPlay()
{
	Super::BeginPlay();

	UUISystemFunctions::PushWidgetFromClass(this, BaseWidgetClass);
}
