// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/PlayerControllerRPS.h"

APlayerControllerRPS::APlayerControllerRPS()
{
	// Turn this off, because, for some reason, the camera is set back to default view target (character) after setting the camera manually to the camera
	// placed in the level
	bAutoManageActiveCameraTarget = false;
}
