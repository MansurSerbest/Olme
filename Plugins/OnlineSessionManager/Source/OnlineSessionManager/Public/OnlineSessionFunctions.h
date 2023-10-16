// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SessionSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnlineSessionFunctions.generated.h"

struct FOnlineSessionSettingsProxy;
/**
 * 
 */
UCLASS()
class ONLINESESSIONMANAGER_API UOnlineSessionFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static USessionSubsystem* GetSessionSubsystem(const UObject* WorldContextObject);

	/*
	 * Calls interface function to create a session
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void CreateSession(const UObject* WorldContextObject, int32 NumPublicConnections, bool bIsLanMatch);

	/*
	 * Calls interface function to update a session
	 */
	static void UpdateSession(const UObject* WorldContextObject, const FOnlineSessionSettingsProxy& Settings);

	/*
	 * Calls interface function to start a session
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void StartSession(const UObject* WorldContextObject);

	/*
	 * Calls interface function to end a session
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void EndSession(const UObject* WorldContextObject);

	/*
	 * Calls interface function to destroy a session
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void DestroySession(const UObject* WorldContextObject);

	/*
	 * Calls interface function to find sessions
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void FindSessions(const UObject* WorldContextObject, int32 MaxSearchResults, bool IsLANQuery);

	/*
	 * Calls interface function to join sessions
	 */
	static void JoinSession(const UObject* WorldContextObject, const FOnlineSessionSearchResult& SessionResult);
};