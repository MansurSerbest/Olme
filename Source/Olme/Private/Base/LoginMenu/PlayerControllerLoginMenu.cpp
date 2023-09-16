// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/LoginMenu/PlayerControllerLoginMenu.h"

#include "Kismet/GameplayStatics.h"

void APlayerControllerLoginMenu::BeginPlay()
{
	Super::BeginPlay();

	if(UGameplayStatics::GetPlatformName() == "Windows")
	{
		SetShowMouseCursor(true);
	}
}
