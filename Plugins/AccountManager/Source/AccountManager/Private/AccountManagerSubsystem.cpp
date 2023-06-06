// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountManagerSubsystem.h"

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
	
	ClientAPI->RegisterPlayFabUser(Request, SuccessDelegate, FailureDelegate);
}

void UAccountManagerSubsystem::OnRegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("REGISTERING SUCCESSFUL!"));
}

void UAccountManagerSubsystem::OnRegisterFailed(const PlayFab::FPlayFabCppError& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("REGISTERING FAILED!"));
}

void UAccountManagerSubsystem::LoginPlayfabAccount(const FString& UsernameOrEmail,
	const FString& Password)
{
	const PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FLoginWithPlayFabRequest Request;
	Request.Username = UsernameOrEmail;
	Request.Password = Password;

	PlayFab::UPlayFabClientAPI::FLoginWithPlayFabDelegate SuccessDelegate;
	SuccessDelegate.BindUObject(this, &UAccountManagerSubsystem::OnLoginSuccess);

	PlayFab::FPlayFabErrorDelegate FailureDelegate;
	FailureDelegate.BindUObject(this, &UAccountManagerSubsystem::OnRegisterFailed);
	
	ClientAPI->LoginWithPlayFab(Request, SuccessDelegate, FailureDelegate);
	
}

void UAccountManagerSubsystem::OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("LOGIN SUCCESSFUL!"));
}

void UAccountManagerSubsystem::OnLoginFailed(const PlayFab::FPlayFabCppError& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("LOGIN FAILED!"));
}
