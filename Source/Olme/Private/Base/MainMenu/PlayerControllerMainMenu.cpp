// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MainMenu/PlayerControllerMainMenu.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerMainMenu::BeginPlay()
{
	Super::BeginPlay();
	
	if(UGameplayStatics::GetPlatformName() == "Windows")
	{
		SetShowMouseCursor(true);
	}
}
