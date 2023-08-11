// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LoginMenu.h"

#include "AccountManagerFunctions.h"
#include "AccountManagerSubsystem.h"
#include "UISystemFunctions.h"
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

#if WITH_EDITOR
	if(GetOwningPlayer()->GetWorld()->WorldType == EWorldType::PIE)
	{
		if (GetWorld()->GetNetMode() == NM_Standalone)
		{
			int PlayerNr = GPlayInEditorID;
			FString UserName{};
			FString Password{TEXT("KoesKoes03")};
			switch(PlayerNr)
			{
			case 0:
				UserName = TEXT("saricari92");
				break;
			case 1:
				UserName = TEXT("neskek92");
				break;
			case 2:
				UserName = TEXT("manser92");
				break;
			}
			
			OnLoginFinishedDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginFinished);
			UAccountManagerFunctions::LoginPlayfabAccount(GetOwningPlayer(), UserName, Password);
			LoginInThrobber->SetVisibility(ESlateVisibility::Visible);
		}
	}
#endif
	
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
	UUISystemFunctions::ReplaceWidgetFromClass(GetOwningPlayer(), RegisterAccountWidgetClass);
}

void ULoginMenu::OnLoginFinished(bool Result)
{
	UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.Remove(OnLoginFinishedDelegateHandle);
	if(Result)
	{
		UUISystemFunctions::ReplaceWidgetFromClass(GetOwningPlayer(), MenuWidgetClass);
	}
	else
	{
		RetryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	LoginInThrobber->SetVisibility(ESlateVisibility::Hidden);
}
