// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LoginMenu.h"

#include "AccountManagerFunctions.h"
#include "AccountManagerSubsystem.h"
#include "UISystemBPLibrary.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

void ULoginMenu::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnPressed.AddDynamic(this, &ULoginMenu::LoginPlayfabAccount);
	RegisterButton->OnPressed.AddDynamic(this, &ULoginMenu::RegisterAccount);

	RetryText->SetVisibility(ESlateVisibility::Collapsed);
	LoginInThrobber->SetVisibility(ESlateVisibility::Hidden);
}

void ULoginMenu::LoginPlayfabAccount()
{
	// Bind First
	OnLoginFinishedDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginFinished);
	UAccountManagerFunctions::LoginPlayfabAccount(GetOwningPlayer(), UsernamePrompt->GetText().ToString(), PasswordPrompt->GetText().ToString());
	LoginInThrobber->SetVisibility(ESlateVisibility::Visible);
}

void ULoginMenu::RegisterAccount()
{
	UUISystemBPLibrary::ReplaceWidgetFromClass(GetOwningPlayer(), RegisterAccountWidgetClass);
}

void ULoginMenu::OnLoginFinished(bool Result)
{
	UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.Remove(OnLoginFinishedDelegateHandle);
	if(Result)
	{
		UUISystemBPLibrary::ReplaceWidgetFromClass(GetOwningPlayer(), MenuWidgetClass);
	}
	else
	{
		RetryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	LoginInThrobber->SetVisibility(ESlateVisibility::Hidden);
}
