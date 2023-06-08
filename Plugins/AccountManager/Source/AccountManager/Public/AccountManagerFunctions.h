// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AccountManagerFunctions.generated.h"

class UAccountManagerSubsystem;
/* 
*	
*/
UCLASS()
class  ACCOUNTMANAGER_API UAccountManagerFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UAccountManagerSubsystem* GetSubsystem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void RegisterPlayfabAccount(const UObject* WorldContextObject, const FString& Email, const FString& Username, const FString& Password);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void LoginPlayfabAccount(const UObject* WorldContextObject, const FString& UsernameOrEmail, const FString& Password);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FString GetPlayfabId(const UObject* WorldContextObject);
};
