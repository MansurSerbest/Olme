// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SessionResultEntry.h"

#include "OnlineSessionFunctions.h"

void USessionResultEntry::Init(const FOnlineSessionSearchResult& Result)
{
	SessionResult = Result;

	SessionNameText->SetText(FText::FromString(Result.Session.GetSessionIdStr()));
	PingText->SetText(FText::FromString(FString::FromInt(Result.PingInMs)));

	const int32 CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections - Result.Session.NumOpenPublicConnections;
	const int32 MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
	PlayerNumberText->SetText(FText::Format(FText::FromString("{0}/{1}"), CurrentPlayers, MaxPlayers));
}

void USessionResultEntry::NativeConstruct()
{
	Super::NativeConstruct();

	JoinBtn->OnPressed.AddDynamic(this, &USessionResultEntry::USessionResultEntry::JoinSession);

	if(USessionSubsystem* Subsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		Subsystem->OnJoinGameSessionCompleteEvent.AddUObject(this, &USessionResultEntry::OnJoinSession);
	}
}

void USessionResultEntry::JoinSession()
{
	UOnlineSessionFunctions::JoinSession(GetOwningPlayer(), SessionResult);
}

void USessionResultEntry::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if(Result == EOnJoinSessionCompleteResult::Type::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession Success!"))
	}
	else if(Result == EOnJoinSessionCompleteResult::Type::UnknownError)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession UnknownError!"))
	}
	else if(Result == EOnJoinSessionCompleteResult::Type::AlreadyInSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession AlreadyInSession!"))
	}
	else if(Result == EOnJoinSessionCompleteResult::Type::SessionIsFull)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession SessionIsFull!"))
	}
	else if(Result == EOnJoinSessionCompleteResult::Type::CouldNotRetrieveAddress)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession CouldNotRetrieveAddress!"))
	}
	else if(Result == EOnJoinSessionCompleteResult::Type::SessionDoesNotExist)
	{
		UE_LOG(LogTemp, Warning, TEXT("JoinSession SessionDoesNotExist!"))
	}
	
}
