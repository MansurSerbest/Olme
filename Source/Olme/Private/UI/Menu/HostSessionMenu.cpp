// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/HostSessionMenu.h"

#include "OnlineSessionFunctions.h"
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
		UE_LOG(LogOlme, Warning, TEXT("ON CREATE SESSION SUCCESSFUL"));
		UGameplayStatics::OpenLevel(GetOwningPlayer(), FName(TEXT("MAP_Lobby")), true, TEXT("listen"));
	}
}
