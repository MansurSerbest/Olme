// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/FindSessionMenu.h"
#include "UI/Menu/SessionResultEntry.h"
#include "OnlineSessionFunctions.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/OnlineSession.h"

void UFindSessionMenu::Setup()
{
	FindSessions();
}

void UFindSessionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(USessionSubsystem* Subsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		Subsystem->OnFindSessionsCompleteEvent.AddUObject(this, &UFindSessionMenu::OnSessionFound);
	}
}

void UFindSessionMenu::OnSessionFound(const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful) const
{
	for(const FOnlineSessionSearchResult& Result : SessionResults)
	{
		if(USessionResultEntry* Entry = CreateWidget<USessionResultEntry>(GetOwningPlayer(), SessionResultType, NAME_Name))
		{
			Entry->Init(Result);
			ListOfSessions->AddChild(Entry);
		}
	}
}

void UFindSessionMenu::FindSessions()
{
	ListOfSessions->ClearChildren();
	UOnlineSessionFunctions::FindSessions(GetOwningPlayer(), 10, true);
}
