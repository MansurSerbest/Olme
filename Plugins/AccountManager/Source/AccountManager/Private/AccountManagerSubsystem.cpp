// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountManagerSubsystem.h"

#include "AccountManager.h"
#include "PlayFab.h"
#include "PlayFabClientDataModels.h"
#include "Core/PlayFabClientAPI.h"

void UAccountManagerSubsystem::RegisterPlayfabAccount(const FString& Email, const FString& Username, const FString& Password)
{
	const PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FRegisterPlayFabUserRequest Request;
	Request.Email = Email;
	Request.Username = Username;
	Request.Password = Password;

	PlayFab::UPlayFabClientAPI::FRegisterPlayFabUserDelegate SuccessDelegate;
	SuccessDelegate.BindUObject(this, &UAccountManagerSubsystem::OnRegisterSuccess);

	PlayFab::FPlayFabErrorDelegate FailureDelegate;
	FailureDelegate.BindUObject(this, &UAccountManagerSubsystem::OnRegisterFailed);
	
	if(!ClientAPI->RegisterPlayFabUser(Request, SuccessDelegate, FailureDelegate))
	{
		OnRegisterPlayfabAccountDelegate.Broadcast(false);
	}
}

void UAccountManagerSubsystem::OnRegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result)
{
	UE_LOG(LogAccountManager, Log, TEXT("REGISTERING SUCCESSFUL!"));
	OnRegisterPlayfabAccountDelegate.Broadcast(true);
	PlayfabUsernameCached = Result.PlayFabId;
}

void UAccountManagerSubsystem::OnRegisterFailed(const PlayFab::FPlayFabCppError& Result)
{
	UE_LOG(LogAccountManager, Warning, TEXT("REGISTERING FAILED!"));
	OnRegisterPlayfabAccountDelegate.Broadcast(false);
}

void UAccountManagerSubsystem::LoginPlayfabAccount(const FString& UsernameOrEmail, const FString& Password)
{
	const PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FLoginWithPlayFabRequest Request;
	Request.Username = UsernameOrEmail;
	Request.Password = Password;

	PlayFab::UPlayFabClientAPI::FLoginWithPlayFabDelegate SuccessDelegate;
	SuccessDelegate.BindUObject(this, &UAccountManagerSubsystem::OnLoginSuccess);

	PlayFab::FPlayFabErrorDelegate FailureDelegate;
	FailureDelegate.BindUObject(this, &UAccountManagerSubsystem::OnLoginFailed);
	
	if(!ClientAPI->LoginWithPlayFab(Request, SuccessDelegate, FailureDelegate))
	{
		OnLoginPlayfabAccountDelegate.Broadcast(false);
	}
}

void UAccountManagerSubsystem::OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	const PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	// Request
	PlayFab::ClientModels::FGetAccountInfoRequest Request;
	// OnSuccess Delegate
	PlayFab::UPlayFabClientAPI::FGetAccountInfoDelegate OnSucces;
	OnSucces.BindLambda([&UserName = this->PlayfabUsernameCached](const PlayFab::ClientModels::FGetAccountInfoResult& Result)->void
	{
		//UE_LOG(LogAccountManager, Log, TEXT("LOGIN SUCCESSFUL! Playerfab id before the change: %s"), *UserName);
		UserName = Result.AccountInfo->Username;
		UE_LOG(LogAccountManager, Log, TEXT("LOGIN SUCCESSFUL! Playerfab id: %s"), *UserName);
	});
	// OnFailure Delegate
	PlayFab::FPlayFabErrorDelegate OnFailure;
	OnFailure.BindLambda([this](const PlayFab::FPlayFabCppError& Result)->void
	{
		
	});
	// Call Get Account API
	ClientAPI->GetAccountInfo(Request, OnSucces, OnFailure);
	
	OnLoginPlayfabAccountDelegate.Broadcast(true);
}

void UAccountManagerSubsystem::OnLoginFailed(const PlayFab::FPlayFabCppError& Result)
{
	UE_LOG(LogAccountManager, Warning, TEXT("LOGIN FAILED!"));
	OnLoginPlayfabAccountDelegate.Broadcast(false);
}

FString UAccountManagerSubsystem::GetPlayfabId() const
{
	return PlayfabUsernameCached;
}
