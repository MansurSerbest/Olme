// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/RPS/PlayerStateRPS.h"

#include "Base/RPS/GameStateRPS.h"
#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

APlayerStateRPS::APlayerStateRPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerStateRPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStateRPS, bIsReady);
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

void APlayerStateRPS::OnRep_Score()
{
	Super::OnRep_Score();

	if(ACharacterRPS* Character = Cast<ACharacterRPS>(GetPawn()))
	{
		Character->SetScore(GetScore());
	}
}

void APlayerStateRPS::ToggleIsReady_Server_Implementation()
{
	bIsReady = !bIsReady;

	OnRep_IsReady();

	if(AGameStateRPS* GameState = Cast<AGameStateRPS>(UGameplayStatics::GetGameState(this)))
	{
		GameState->TryStartRound();
	}
}

void APlayerStateRPS::SetupStartMatch()
{
}

void APlayerStateRPS::OnRep_CustomName()
{
	Super::OnRep_CustomName();
	
	if(ACharacterRPS* Character = Cast<ACharacterRPS>(GetPawn()))
	{
		Character->SetCharacterName(CustomName);
		SetActorTickEnabled(false);
	}
}

void APlayerStateRPS::OnRep_IsReady()
{
	if(AGameStateRPS* GS = Cast<AGameStateRPS>(UGameplayStatics::GetGameState(this)))
	{
		ACharacterRPS* Character = Cast<ACharacterRPS>(GetPawn());
		if(Character && !GS->GetMatchStarted())
		{
			Character->SetCheckBoxes(bIsReady);
		}
	}
	

}
