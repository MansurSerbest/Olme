// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HudSurvival.h"
#include "UISystemFunctions.h"


void AHudSurvival::BeginPlay()
{
	Super::BeginPlay();

	UUISystemFunctions::PushWidgetFromClass(GetOwningPlayerController(), MainWidgetClass);
}
