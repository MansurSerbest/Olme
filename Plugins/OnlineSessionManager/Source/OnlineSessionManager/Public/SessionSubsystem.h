// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SessionSubsystem.generated.h"

struct FOnlineSessionSettingsProxy;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnCreateSessionComplete, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnUpdateSessionComplete, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnStartSessionComplete, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnEndSessionComplete, bool, bIsSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnDestroySessionComplete, bool, Successful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FCSOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful);
DECLARE_MULTICAST_DELEGATE_OneParam(FCSOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);

/**
 * Handles the session functionalities
 */
UCLASS()
class ONLINESESSIONMANAGER_API USessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USessionSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/*
	 * Calls interface function to create a session
	 */
	void CreateSession(int32 NumPublicConnections, bool bIsLanMatch);
	FCSOnCreateSessionComplete OnCreateSessionCompleteEvent;

	/*
	 * Calls interface function to update a session
	 */
	void UpdateSession(const FOnlineSessionSettingsProxy& Settings);
	FCSOnUpdateSessionComplete OnUpdateSessionCompleteEvent;

	/*
	 * Calls interface function to start a session
	 */
	void StartSession();
	FCSOnStartSessionComplete OnStartSessionCompleteEvent;

	/*
	 * Calls interface function to end a session
	 */
	void EndSession();
	FCSOnEndSessionComplete OnEndSessionCompleteEvent;

	/*
	 * Calls interface function to destroy a session
	 */
	void DestroySession();
	FCSOnDestroySessionComplete OnDestroySessionCompleteEvent;

	/*
	 * Calls interface function to find sessions
	 */
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);
	FCSOnFindSessionsComplete OnFindSessionsCompleteEvent;

	/*
	 * Calls interface function to join sessions
	 */
	void JoinGameSession(const FOnlineSessionSearchResult& SessionResult);
	FCSOnJoinSessionComplete OnJoinGameSessionCompleteEvent;

protected:
	/*
	 * Called when CreateSession call is completed
	 */
	void OnCreateSessionCompleted(FName SessionName, bool bIsSuccess);

	/*
	* Called when UpdateSession call is completed
	*/
	void OnUpdateSessionCompleted(FName SessionName, bool bIsSuccess);
	
	/*
	 * Called when StartSession call is completed
	 */
	void OnStartSessionCompleted(FName SessionName, bool bIsSuccess);

	/*
	 * Called when EndSession call is completed
	 */
	void OnEndSessionCompleted(FName SessionName, bool bIsSuccess);

	/*
	 * Called when DestroySession call is completed
	 */
	void OnDestroySessionCompleted(FName SessionName, bool Successful);

	/*
	 * Called when FindSession call is completed
	 */
	void OnFindSessionsCompleted(bool Successful);

	/*
	 * Called when JoinSession call is completed
	 */
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	bool TryTravelToCurrentSession();
	
private:
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
	FDelegateHandle UpdateSessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	FOnEndSessionCompleteDelegate EndSessionCompleteDelegate;
	FDelegateHandle EndSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
};
