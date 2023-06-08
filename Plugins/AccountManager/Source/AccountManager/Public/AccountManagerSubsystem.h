// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabClientDataModels.h"
#include "PlayFabError.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AccountManagerSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterPlayfabAccountDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginPlayfabAccountDelegate, bool);

/**
 * 
 */
UCLASS()
class ACCOUNTMANAGER_API UAccountManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void RegisterPlayfabAccount(const FString& Email, const FString& Username, const FString& Password);
	FOnRegisterPlayfabAccountDelegate OnRegisterPlayfabAccountDelegate;
	void OnRegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result);
	void OnRegisterFailed(const PlayFab::FPlayFabCppError& Result);

	void LoginPlayfabAccount(const FString& UsernameOrEmail, const FString& Password);
	FOnLoginPlayfabAccountDelegate OnLoginPlayfabAccountDelegate;
	void OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
	void OnLoginFailed(const PlayFab::FPlayFabCppError& Result);

	FString GetPlayfabId() const;
	
private:
	FString PlayfabUsernameCached;
};
