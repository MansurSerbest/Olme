// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RockPaperScissors/Input/RPSInputDataAsset.h"
#include "EnhancedInput/Public/InputAction.h"


URPSInputDataAsset::URPSInputDataAsset(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UInputAction> ChooseAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Gameplay/RPS/Input/IA_RPS_Choose.IA_RPS_Choose'"));
	if(ChooseAsset.Succeeded())
	{
		Choose = ChooseAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> ConfirmChoiceAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Gameplay/RPS/Input/IA_RPS_ConfirmChoice.IA_RPS_ConfirmChoice'"));
	if(ConfirmChoiceAsset.Succeeded())
	{
		ConfirmChoice = ConfirmChoiceAsset.Object;
	}
}
