// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/LoginMenu.h"

#include "AccountManagerFunctions.h"
#include "AccountManagerSubsystem.h"
#include "UISystemFunctions.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

void ULoginMenu::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnPressed.AddDynamic(this, &ULoginMenu::LoginEpicGamesAcount);
	RegisterButton->OnPressed.AddDynamic(this, &ULoginMenu::RegisterAccount);
	LoginEpicGamesButton->OnPressed.AddDynamic(this, &ULoginMenu::LoginEpicGamesAcount);

	RetryText->SetVisibility(ESlateVisibility::Collapsed);
	LoginInThrobber->SetVisibility(ESlateVisibility::Hidden);

#if WITH_EDITOR
	AutoLoginWithEpicGames();
#endif
	
}

void ULoginMenu::LoginPlayfabAccount()
{
	// Bind First
	OnLoginFinishedPlayfabDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginCompletedPlayfab);
	UAccountManagerFunctions::LoginPlayfabAccount(GetOwningPlayer(), UsernamePrompt->GetText().ToString(), PasswordPrompt->GetText().ToString());
	StartLogin();
}

void ULoginMenu::LoginEpicGamesAcount()
{
	OnLoginFinishedEpicGamesDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginCompleteEpicGamesAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginCompletedEpicGames);
	UAccountManagerFunctions::LoginEpicGamesAccount(GetOwningPlayer());
	StartLogin();
}

void ULoginMenu::RegisterAccount()
{
	UUISystemFunctions::ReplaceWidgetFromClass(GetOwningPlayer(), RegisterAccountWidgetClass);
}

void ULoginMenu::OnLoginCompletedPlayfab(bool Result)
{
	FinishLogin();
	UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.Remove(OnLoginFinishedPlayfabDelegateHandle);
	if(Result)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwningPlayer(), MainMenuLevel);
	}
	else
	{
		RetryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void ULoginMenu::StartLogin()
{
	LoginInThrobber->SetVisibility(ESlateVisibility::Visible);
}

void ULoginMenu::FinishLogin()
{
	LoginInThrobber->SetVisibility(ESlateVisibility::Hidden);
}

void ULoginMenu::OnLoginCompletedEpicGames(bool Result)
{
	FinishLogin();
	UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginCompleteEpicGamesAccountDelegate.Remove(OnLoginFinishedEpicGamesDelegateHandle);
	if(Result)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwningPlayer(), MainMenuLevel);
	}
	else
	{
		RetryText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

#if WITH_EDITOR
void ULoginMenu::AutoLoginWithPlayfab()
{
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
				UserName = TEXT("neskekgames");
				break;
			case 2:
				UserName = TEXT("manser92");
				break;
			}
			
			OnLoginFinishedPlayfabDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginPlayfabAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginCompletedPlayfab);
			UAccountManagerFunctions::LoginPlayfabAccount(GetOwningPlayer(), UserName, Password);
			LoginInThrobber->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ULoginMenu::AutoLoginWithEpicGames()
{
	if(GetOwningPlayer()->GetWorld()->WorldType == EWorldType::PIE)
	{
		FOnlineAccountCredentials Credentials;
		Credentials.Type = TEXT("developer");
		Credentials.Id = TEXT("localhost:8081");
		if (GetWorld()->GetNetMode() == NM_Standalone)
		{
			switch(GPlayInEditorID)
			{
			case 0:
				Credentials.Token = TEXT("NeskekGames");
				break;
			case 1:
				Credentials.Token = TEXT("ManSer92");
				break;
			case 2:
				Credentials.Token = TEXT("Saricari92");
				break;
			default:
					break; // Do nothing
			}
		}

		OnLoginFinishedEpicGamesDelegateHandle = UAccountManagerFunctions::GetSubsystem(GetOwningPlayer())->OnLoginCompleteEpicGamesAccountDelegate.AddUObject(this, &ULoginMenu::OnLoginCompletedEpicGames);
		UAccountManagerFunctions::LoginWithCredentialsEpicGamesAccount(GetOwningPlayer(), Credentials);
		StartLogin();
	}
}
#endif

