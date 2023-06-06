// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/RegisterMenu.h"
#include "AccountManagerFunctions.h"

void URegisterMenu::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterButton->OnPressed.AddDynamic(this, &URegisterMenu::RegisterPlayfabAccount);
}

void URegisterMenu::RegisterPlayfabAccount()
{
	UAccountManagerFunctions::RegisterPlayfabAccount(GetOwningPlayer(), EmailPrompt->GetText().ToString(), UsernamePrompt->GetText().ToString(), PasswordPrompt->GetText().ToString());
}
