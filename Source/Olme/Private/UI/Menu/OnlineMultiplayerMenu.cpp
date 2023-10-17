// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/OnlineMultiplayerMenu.h"

#include "OnlineSessionFunctions.h"
#include "UISystemFunctions.h"
#include "UI/Menu/FindSessionMenu.h"

void UOnlineMultiplayerMenu::NativeConstruct()
{
	Super::NativeConstruct();

	HostSessionBtn->OnClicked.AddDynamic(this, &UOnlineMultiplayerMenu::OnHostSessionPressed);
	FindSessionBtn->OnClicked.AddDynamic(this, &UOnlineMultiplayerMenu::OnFindSessionPressed);
	OptionsBtn->OnClicked.AddDynamic(this, &UOnlineMultiplayerMenu::OnOptionsPressed);
	BackBtn->OnClicked.AddDynamic(this, &UOnlineMultiplayerMenu::OnBackPressed);
}

void UOnlineMultiplayerMenu::OnHostSessionPressed()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UOnlineMultiplayerMenu::OnFindSessionPressed()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
	if(UFindSessionMenu* FindSessionMenu = Cast<UFindSessionMenu>(WidgetSwitcher->GetActiveWidget()))
	{
		FindSessionMenu->Setup();
	}
}

void UOnlineMultiplayerMenu::OnOptionsPressed()
{
	WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UOnlineMultiplayerMenu::OnBackPressed()
{
	UUISystemFunctions::PopWidget(GetOwningPlayer());
}
