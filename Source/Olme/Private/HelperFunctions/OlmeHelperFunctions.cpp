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
		UE_LOG(LogOlme, Warning, TEXT("[%d]: %s called on NM_ListenServer!"), PlayerNr, *Text);
		break;
	case NM_Client:
		UE_LOG(LogOlme, Warning, TEXT("[%d]: %s called on NM_Client!"),PlayerNr, *Text);
		break;
	case NM_Standalone:
		UE_LOG(LogOlme, Warning, TEXT("[%d]: %s on NM_Standalone!"),PlayerNr, *Text);
		break;
	case NM_DedicatedServer:
		UE_LOG(LogOlme, Warning, TEXT("[%d]: %s on NM_DedicatedServer!"),PlayerNr, *Text);
		break;
	case NM_MAX:
		UE_LOG(LogOlme, Warning, TEXT("[%d]: %s on NM_MAX!"),PlayerNr, *Text);
		break;
	}
}
