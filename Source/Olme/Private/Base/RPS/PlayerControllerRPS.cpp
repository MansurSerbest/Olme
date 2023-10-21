// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/PlayerControllerRPS.h"

#include "OnlineSessionFunctions.h"
#include "Base/GameInstance/GameInstanceOlme.h"
#include "Kismet/GameplayStatics.h"

APlayerControllerRPS::APlayerControllerRPS()
{
	// Turn this off, because, for some reason, the camera is set back to default view target (character) after setting the camera manually to the camera
	// placed in the level
	bAutoManageActiveCameraTarget = false;
}

void APlayerControllerRPS::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void APlayerControllerRPS::LeaveGame_Implementation()
{
	if(UGameInstanceOlme* Instance = Cast<UGameInstanceOlme>(UGameplayStatics::GetGameInstance(this)))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, Instance->GetMainMenuMap());
		UOnlineSessionFunctions::DestroySession(this);
	}
}
