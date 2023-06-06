// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabClientDataModels.h"
#include "PlayFabError.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AccountManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ACCOUNTMANAGER_API UAccountManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterPlayfabAccount(const FString& Email, const FString& Username, const FString& Password);
	void OnRegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result);
	void OnRegisterFailed(const PlayFab::FPlayFabCppError& Result);

	void LoginPlayfabAccount(const FString& UsernameOrEmail, const FString& Password);
	void OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
	void OnLoginFailed(const PlayFab::FPlayFabCppError& Result);
	
private:
	FString UsernameCached;
};
