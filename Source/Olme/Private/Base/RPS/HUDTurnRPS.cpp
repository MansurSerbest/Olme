// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/HUDTurnRPS.h"

#include "UISystemFunctions.h"
#include "Gameplay/RockPaperScissors/UI/WidgetRPS.h"

void AHUDTurnRPS::BeginPlay()
{
	Super::BeginPlay();

	UWidgetRPS* Widget = CreateWidget<UWidgetRPS>(GetOwningPlayerController(), MainWidgetClass);
	if(Widget)
	{
		UUISystemFunctions::PushWidgetFromInstance(this, Widget);
	}
}
