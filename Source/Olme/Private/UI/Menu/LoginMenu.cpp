// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/LoginMenu.h"

#include "AccountManagerFunctions.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void ULoginMenu::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnPressed.AddDynamic(this, &ULoginMenu::LoginPlayfabAccount);
}

void ULoginMenu::LoginPlayfabAccount()
{
	UAccountManagerFunctions::LoginPlayfabAccount(GetOwningPlayer(), UsernamePrompt->GetText().ToString(), PasswordPrompt->GetText().ToString());
}
