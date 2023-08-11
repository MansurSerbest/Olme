// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API APlayerControllerMainMenu : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
