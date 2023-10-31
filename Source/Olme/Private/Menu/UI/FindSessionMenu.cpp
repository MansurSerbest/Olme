// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/FindSessionMenu.h"
#include "Menu/UI/SessionResultEntry.h"
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
}

void UFindSessionMenu::OnSessionFound(const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful) const
{
	if(USessionSubsystem* Subsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		Subsystem->OnFindSessionsCompleteEvent.Remove(FindSessionCompleteHandle);
	}
	
	for(const FOnlineSessionSearchResult& Result : SessionResults)
	{
		if(USessionResultEntry* Entry = CreateWidget<USessionResultEntry>(GetOwningPlayer(), SessionResultType, NAME_Name))
		{
			Entry->Init(Result);
			ListOfSessions->AddChild(Entry);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("All Children: \n"));
	for(const auto i : ListOfSessions->GetAllChildren())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s\n"), *i->GetName());
	}
}

void UFindSessionMenu::FindSessions()
{
	ListOfSessions->ClearChildren();

	if(USessionSubsystem* Subsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		FindSessionCompleteHandle = Subsystem->OnFindSessionsCompleteEvent.AddUObject(this, &UFindSessionMenu::OnSessionFound);
		UOnlineSessionFunctions::FindSessions(GetOwningPlayer(), 10, true);
	}
}
