// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/PlayerStateRPS.h"

#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Olme/Olme.h"

APlayerStateRPS::APlayerStateRPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerStateRPS::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(ACharacterRPS* Character = Cast<ACharacterRPS>(GetPawn()))
	{
		UOlmeHelperFunctions::PrintNetMode(this, *FString::Format(TEXT("TICK: Name of {0} is {1}"), {*GetName(), *CustomName}));
		Character->SetCharacterName(CustomName);
		SetActorTickEnabled(false);
	}
}

void APlayerStateRPS::OnRep_CustomName()
{
	Super::OnRep_CustomName();
	
	if(ACharacterRPS* Character = Cast<ACharacterRPS>(GetPawn()))
	{
		UOlmeHelperFunctions::PrintNetMode(this, *FString::Format(TEXT("ONREP: Name of {0} is {1}"), {*GetName(), *CustomName}));
		Character->SetCharacterName(CustomName);
		SetActorTickEnabled(false);
	}
}
