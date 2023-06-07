// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/RegisterMenu.h"
#include "AccountManagerFunctions.h"
#include "AccountManagerSubsystem.h"
#include "UISystemBPLibrary.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

void URegisterMenu::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterButton->OnPressed.AddDynamic(this, &URegisterMenu::RegisterPlayfabAccount);
	RetryText->SetVisibility(ESlateVisibility::Collapsed);
	RegisteringThrobber->SetVisibility(ESlateVisibility::Hidden);
	BackButton->OnPressed.AddDynamic(this, &URegisterMenu::Back);
}

void URegisterMenu::RegisterPlayfabAccount()
{
	// Bind first
	OnRegisterFinishedDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnRegisterPlayfabAccountDelegate.AddUObject(this, &URegisterMenu::OnRegisterFinished);
	UAccountManagerFunctions::RegisterPlayfabAccount(GetOwningPlayer(), EmailPrompt->GetText().ToString(), UsernamePrompt->GetText().ToString(), PasswordPrompt->GetText().ToString());
	RegisteringThrobber->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void URegisterMenu::Back()
{
	UUISystemBPLibrary::ReplaceWidgetFromClass(GetOwningPlayer(), LoginWidgetClass);
}

void URegisterMenu::OnRegisterFinished(bool Result)
{
	UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnRegisterPlayfabAccountDelegate.Remove(OnRegisterFinishedDelegateHandle);
	if(Result)
	{
		UUISystemBPLibrary::ReplaceWidgetFromClass(GetOwningPlayer(), MenuWidgetClass);
	}
	else
	{
		RetryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	RegisteringThrobber->SetVisibility(ESlateVisibility::Hidden);
}
