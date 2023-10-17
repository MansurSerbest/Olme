// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/HostSessionMenu.h"

#include "OnlineSessionFunctions.h"
#include "Base/GameInstance/GameInstanceOlme.h"
#include "GameFramework/OnlineSession.h"
#include "Kismet/GameplayStatics.h"
#include "Olme/Olme.h"
#include "OnlineSessionManager/Public/SessionSubsystem.h"

void UHostSessionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	HostSessionBtn->OnClicked.AddDynamic(this, &UHostSessionMenu::OnPressedHostSessionBtn);
}

void UHostSessionMenu::OnPressedHostSessionBtn()
{
	if(USessionSubsystem* SessionSubsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		SessionSubsystem->OnCreateSessionCompleteEvent.AddDynamic(this, &UHostSessionMenu::OnCreateSession);
		UOnlineSessionFunctions::CreateSession(GetWorld(), 6, true);
	}
}

void UHostSessionMenu::OnCreateSession(bool Success)
{
	if(USessionSubsystem* SessionSubsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer()))
	{
		SessionSubsystem->OnCreateSessionCompleteEvent.RemoveDynamic(this, &UHostSessionMenu::OnCreateSession);
	}
	
	if(Success)
	{
		if(UGameInstanceOlme* Instance = Cast<UGameInstanceOlme>(UGameplayStatics::GetGameInstance(GetOwningPlayer())))
		{
			UE_LOG(LogOlme, Log, TEXT("UHostSessionMenu::OnCreateSession: ON CREATE SESSION SUCCESSFUL"));
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwningPlayer(), Instance->GetLobbyMap(), true, TEXT("listen"));
		}

	}
}
