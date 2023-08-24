// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountManagerSubsystem.h"

#include "AccountManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
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
	UsernameCached = Result.PlayFabId;
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
	OnSucces.BindLambda([&UserName = this->UsernameCached](const PlayFab::ClientModels::FGetAccountInfoResult& Result)->void
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

FString UAccountManagerSubsystem::GetUserNameCached() const
{
	return UsernameCached;
}

void UAccountManagerSubsystem::LoginEpicGamesAccount()
{
	/*
	This function will access the EOS OSS via the OSS identity interface to log first into Epic Account Services, and then into Epic Game Services.
	It will bind a delegate to handle the callback event once login call succeeeds or fails. 
	All functions that access the OSS will have this structure: 1-Get OSS interface, 2-Bind delegate for callback and 3-Call OSS interface function (which will call the correspongin EOS OSS function)
	*/
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()/*, FName("EOS")*/);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	// If you're logged in, don't try to login again.
	// This can happen if your player travels to a dedicated server or different maps as BeginPlay() will be called each time.
    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);
	ELoginStatus::Type LoginStatus = Identity->GetLoginStatus(0);
	if(NetId != nullptr && LoginStatus == ELoginStatus::LoggedIn)
	{
		SetUserNameCachedEpicGamesAccount(Identity);
		return;
	}

	/* This binds a delegate so we can run our function when the callback completes. 0 represents the player number.
	You should parametrize this Login function and pass the parameter here for splitscreen. 
	*/
	FOnLoginCompleteDelegate OnLoginCompleteDelegate;
	OnLoginCompleteDelegate.BindLambda(	[Identity, this](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
	{
		/*
		Tutorial 2: This function handles the callback from logging in. You should not proceed with any EOS features until this function is called.
		This function will remove the delegate that was bound in the Login() function.
		*/
		if (bWasSuccessful)
		{
			UE_LOG(LogAccountManager, Log, TEXT("Login callback completed!"));
			SetUserNameCachedEpicGamesAccount(Identity);
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(true);
		}
		else //Login failed
		{
			// If your game is online only, you may want to return an error to the user and return to a menu that uses a different GameMode/PlayerController.
	 
			UE_LOG(LogAccountManager, Warning, TEXT("EOS login failed.")); //Print sign in failure in logs as a warning.
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(false);
		}
 
		Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
		LoginDelegateHandle.Reset();
	});
	
	LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(0, OnLoginCompleteDelegate);

	// Grab command line parameters. If empty call hardcoded login function - Hardcoded login function useful for Play In Editor.
	FString AuthType;
	FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);
	
	// if parameter is NOT empty, we can autologin
	if(!AuthType.IsEmpty())
	{
		UE_LOG(LogAccountManager, Log, TEXT("Logging into EOS..."));

		if(!Identity->AutoLogin(0))
		{
			UE_LOG(LogAccountManager, Warning, TEXT("Failed to login..."));
			// Clear the handle here already
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(false);
		}
	}
	else
	{
		FOnlineAccountCredentials Credentials("accountportal", "", "");
		UE_LOG(LogAccountManager, Log, TEXT("Loggin into EOS..."));

		if(!Identity->Login(0, Credentials))
		{
			UE_LOG(LogAccountManager, Warning, TEXT("Failed to login..."));
			// Clear the handle here already
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(false);
		}
	}
}

void UAccountManagerSubsystem::LoginWithCredentialsEpicGamesAccount(const FOnlineAccountCredentials& Credentials)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	// If you're logged in, don't try to login again.
	// This can happen if your player travels to a dedicated server or different maps as BeginPlay() will be called each time.
    FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);
	ELoginStatus::Type LoginStatus = Identity->GetLoginStatus(0);
	if(NetId != nullptr && LoginStatus == ELoginStatus::LoggedIn)
	{
		SetUserNameCachedEpicGamesAccount(Identity);
		return;
	}
	
	FOnLoginCompleteDelegate OnLoginCompleteDelegate;
	OnLoginCompleteDelegate.BindLambda(	[Identity, this](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
	{
		/*
		Tutorial 2: This function handles the callback from logging in. You should not proceed with any EOS features until this function is called.
		This function will remove the delegate that was bound in the Login() function.
		*/
		if (bWasSuccessful)
		{
			UE_LOG(LogAccountManager, Log, TEXT("Login callback completed!"));
			SetUserNameCachedEpicGamesAccount(Identity);
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(true);
		}
		else //Login failed
		{
			// If your game is online only, you may want to return an error to the user and return to a menu that uses a different GameMode/PlayerController.
	 
			UE_LOG(LogAccountManager, Warning, TEXT("EOS login failed.")); //Print sign in failure in logs as a warning.
			OnLoginCompleteEpicGamesAccountDelegate.Broadcast(false);
		}
 
		Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
		LoginDelegateHandle.Reset();
	});
	LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(0, OnLoginCompleteDelegate);
	
	UE_LOG(LogAccountManager, Log, TEXT("Loggin into EOS..."));
	
	if(!Identity->Login(0, Credentials))
	{
		UE_LOG(LogAccountManager, Warning, TEXT("Failed to login..."));
		// Clear the handle here already
		Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
		LoginDelegateHandle.Reset();
		OnLoginCompleteEpicGamesAccountDelegate.Broadcast(false);
	}
}

void UAccountManagerSubsystem::SetUserNameCachedEpicGamesAccount(const IOnlineIdentityPtr& Identity)
{
	TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Identity->GetUniquePlayerId(0));
	UsernameCached = Account->GetDisplayName();
}
