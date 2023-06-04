// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/HostSessionMenu.h"

#include "OnlineSessionFunctions.h"
#include "GameFramework/OnlineSession.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionManager/Public/SessionSubsystem.h"

void UHostSessionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	USessionSubsystem* SessionSubsystem = UOnlineSessionFunctions::GetSessionSubsystem(GetOwningPlayer());
	if(IsValid(SessionSubsystem))
	{
		SessionSubsystem->OnCreateSessionCompleteEvent.AddDynamic(this, &UHostSessionMenu::OnCreateSession);
	}
	
	HostSessionBtn->OnClicked.AddDynamic(this, &UHostSessionMenu::OnPressedHostSessionBtn);
}

void UHostSessionMenu::OnPressedHostSessionBtn()
{
	UOnlineSessionFunctions::CreateSession(GetWorld(), 6, true);
}

void UHostSessionMenu::OnCreateSession(bool Success)
{
	if(Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("ON CREATE SESSION SUCCESSFUL"));
		UGameplayStatics::OpenLevel(GetOwningPlayer(), FName(TEXT("MAP_Lobby")), true, TEXT("listen"));
	}
}
