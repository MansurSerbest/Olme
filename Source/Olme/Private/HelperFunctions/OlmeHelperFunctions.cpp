// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunctions/OlmeHelperFunctions.h"

#include "Olme/Olme.h"

void UOlmeHelperFunctions::PrintNetMode(const UObject* WorldContextObject, const FString& Text)
{
	UWorld* World = WorldContextObject->GetWorld();
	if(!World)
	{
		return;
	}

	int PlayerNr = -1;
#if UE_EDITOR
	if(World->WorldType == EWorldType::PIE)
	{
		PlayerNr = GPlayInEditorID;
	}
#endif
	
	switch (World->GetNetMode())
	{
	case NM_ListenServer:
		UE_LOG(LogOlme, Log, TEXT("[NM_ListenServer][%d]: %s!"), PlayerNr, *Text);
		break;
	case NM_Client:
		UE_LOG(LogOlme, Log, TEXT("[NM_Client][%d]: %s!"),PlayerNr, *Text);
		break;
	case NM_Standalone:
		UE_LOG(LogOlme, Log, TEXT("[NM_Standalone][%d]: %s!"),PlayerNr, *Text);
		break;
	case NM_DedicatedServer:
		UE_LOG(LogOlme, Log, TEXT("[NM_DedicatedServer][%d]: %s!"),PlayerNr, *Text);
		break;
	case NM_MAX:
		UE_LOG(LogOlme, Log, TEXT("[NM_MAX][%d]: %s!"),PlayerNr, *Text);
		break;
	}
}

int32 UOlmeHelperFunctions::ShiftInRotation(const int Size, const int Direction, int Idx)
{
	Idx += Direction;

	if(Idx < 0)
	{
		Idx = Size -1;
	}
	else if(Idx > Size - 1)
	{
		Idx = 0;
	}

	return Idx;
}

bool UOlmeHelperFunctions::IsPawnLocallyOwned(const APawn* Pawn)
{
	if(APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
	{
		return PC->IsLocalController();
	}

	// If this is called on a client and the Pawn is another client pawn, the cast to APlayerController will return nullptr because Playercontrollers of other
	// Players don't exist on clients' machines
	return false;
}
