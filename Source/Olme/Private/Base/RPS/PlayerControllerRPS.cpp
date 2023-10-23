// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/PlayerControllerRPS.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "OnlineSessionFunctions.h"
#include "Base/GameInstance/GameInstanceOlme.h"
#include "Kismet/GameplayStatics.h"

APlayerControllerRPS::APlayerControllerRPS(const FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Turn this off, because, for some reason, the camera is set back to default view target (character) after setting the camera manually to the camera
	// placed in the level
	bAutoManageActiveCameraTarget = false;

	ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextFillObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Gameplay/RPS/Input/IMC_RPS.IMC_RPS'"));
	if(InputMappingContextFillObj.Succeeded())
	{
		InputMappingContext = InputMappingContextFillObj.Object;
	}
}

void APlayerControllerRPS::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if(InputMappingContext)
			{
				const UInputMappingContext* InputMapping = Cast<UInputMappingContext>(InputMappingContext);
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}

void APlayerControllerRPS::LeaveGame_Implementation()
{
	if(UGameInstanceOlme* Instance = Cast<UGameInstanceOlme>(UGameplayStatics::GetGameInstance(this)))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, Instance->GetMainMenuMap());
		UOnlineSessionFunctions::DestroySession(this);
	}
}
