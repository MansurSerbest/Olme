// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HudSurvival.h"
#include "UISystemBPLibrary.h"


void AHudSurvival::BeginPlay()
{
	Super::BeginPlay();

	UUISystemBPLibrary::PushWidgetFromClass(GetOwningPlayerController(), MainWidgetClass);
}
