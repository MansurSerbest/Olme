// Copyright Epic Games, Inc. All Rights Reserved.

#include "AccountManagerFunctions.h"
#include "AccountManager/Public/AccountManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

UAccountManagerSubsystem* UAccountManagerFunctions::GetSubsystem(const UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UAccountManagerSubsystem* Subsystem = GameInstance->GetSubsystem<UAccountManagerSubsystem>();

	return Subsystem;
}

void UAccountManagerFunctions::RegisterPlayfabAccount(const UObject* WorldContextObject, const FString& Email, const FString& Username, const FString& Password)
{
	if(UAccountManagerSubsystem* Subsystem = GetSubsystem(WorldContextObject))
	{
		Subsystem->RegisterPlayfabAccount(Email, Username, Password);
	}
}

void UAccountManagerFunctions::LoginPlayfabAccount(const UObject* WorldContextObject, const FString& UsernameOrEmail, const FString& Password)
{
	if(UAccountManagerSubsystem* Subsystem = GetSubsystem(WorldContextObject))
	{
		Subsystem->LoginPlayfabAccount(UsernameOrEmail, Password);
	}
}

FString UAccountManagerFunctions::GetCachedUsername(const UObject* WorldContextObject)
{
	FString ReturnValue;
	if(UAccountManagerSubsystem* Subsystem = GetSubsystem(WorldContextObject))
	{
		ReturnValue = Subsystem->GetUserNameCached();
	}

	return ReturnValue;
}

void UAccountManagerFunctions::LoginEpicGamesAccount(const UObject* WorldContextObject)
{
	if(UAccountManagerSubsystem* Subsystem = GetSubsystem(WorldContextObject))
	{
		Subsystem->LoginEpicGamesAccount();
	}
}

void UAccountManagerFunctions::LoginWithCredentialsEpicGamesAccount(const UObject* WorldContextObject,
	const FOnlineAccountCredentials& Credentials)
{
	if(UAccountManagerSubsystem* Subsystem = GetSubsystem(WorldContextObject))
	{
		Subsystem->LoginWithCredentialsEpicGamesAccount(Credentials);
	}
}
