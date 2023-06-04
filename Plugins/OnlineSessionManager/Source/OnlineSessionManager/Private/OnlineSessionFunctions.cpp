// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineSessionFunctions.h"

#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

USessionSubsystem* UOnlineSessionFunctions::GetSessionSubsystem(const UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	//USessionSubsystem* SessionSubsystem = WorldContextObject->GetWorld()->GetSubsystem<USessionSubsystem>();
	USessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<USessionSubsystem>();

	return SessionSubsystem;
}

void UOnlineSessionFunctions::CreateSession(const UObject* WorldContextObject, int32 NumPublicConnections,
	bool bIsLanMatch)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->CreateSession(NumPublicConnections, bIsLanMatch);
	}
}

void UOnlineSessionFunctions::UpdateSession(const UObject* WorldContextObject)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->UpdateSession();
	}
}

void UOnlineSessionFunctions::StartSession(const UObject* WorldContextObject)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->StartSession();
	}
}

void UOnlineSessionFunctions::EndSession(const UObject* WorldContextObject)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->EndSession();
	}
}

void UOnlineSessionFunctions::DestroySession(const UObject* WorldContextObject)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->DestroySession();
	}
}

void UOnlineSessionFunctions::FindSessions(const UObject* WorldContextObject, int32 MaxSearchResults,
	bool IsLANQuery)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->FindSessions(MaxSearchResults, IsLANQuery);
	}
}

void UOnlineSessionFunctions::JoinSession(const UObject* WorldContextObject,
	const FOnlineSessionSearchResult& SessionResult)
{
	if(USessionSubsystem* SessionSubsystem = GetSessionSubsystem(WorldContextObject))
	{
		SessionSubsystem->JoinGameSession(SessionResult);
	}
}