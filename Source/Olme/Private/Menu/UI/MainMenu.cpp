// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MainMenu.h"


void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SinglePlayerBtn->OnPressed.AddDynamic(this, &UMainMenu::OnPressedSinglePlayerBtn);
	OnlineMultiplayerBtn->OnPressed.AddDynamic(this, &UMainMenu::OnPressedOnlineMultiplayerBtn);
	SettingsBtn->OnPressed.AddDynamic(this, &UMainMenu::OnPressedSettingsBtn);
	ExitBtn->OnPressed.AddDynamic(this, &UMainMenu::OnPressedExitBtn);
}

void UMainMenu::OnPressedSinglePlayerBtn()
{
	UE_LOG(LogTemp, Warning, TEXT("On Pressed Single Player Btn!"));
	OpenSinglePlayerMenu();
}

void UMainMenu::OnPressedOnlineMultiplayerBtn()
{
	UE_LOG(LogTemp, Warning, TEXT("On Pressed Online Multiplayer Btn!"));
	OpenOnlineMultiplayerMenu();
}

void UMainMenu::OnPressedSettingsBtn()
{
	UE_LOG(LogTemp, Warning, TEXT("On Pressed Settings Btn!"));
	OpenSettingsMenu();
}

void UMainMenu::OnPressedExitBtn()
{
	UE_LOG(LogTemp, Warning, TEXT("On Pressed Exit Btn!"));
}
