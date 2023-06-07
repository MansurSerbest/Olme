// Copyright Epic Games, Inc. All Rights Reserved.

#include "UISystemFunctions.h"
#include "UISystem.h"
#include "Kismet/GameplayStatics.h"
#include "UIWorldSubsystem.h"

UUISystemFunctions::UUISystemFunctions(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UUserWidget* UUISystemFunctions::PushWidgetFromClass(UObject* WorldContextObject, TSubclassOf<UUserWidget> Class, bool bPreviousWidgetVisible)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PushWidgetFromClass(Class, bPreviousWidgetVisible);
	}

	return nullptr;
}

UUserWidget* UUISystemFunctions::PushWidgetFromInstance(UObject* WorldContextObject, UUserWidget* NewWidget, bool bPreviousWidgetVisible)
{
	if(UUIWorldSubsystem* Subsystem = UUISystemFunctions::GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PushWidgetFromInstance(NewWidget, bPreviousWidgetVisible);
	}

	return nullptr;
}

UUserWidget* UUISystemFunctions::ReplaceWidgetFromClass(UObject* WorldContextObject, TSubclassOf<UUserWidget> Class)
{
	if(UUIWorldSubsystem* Subsystem = UUISystemFunctions::GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->ReplaceWidgetFromClass(Class, true);
	}

	return nullptr;
}

UUserWidget* UUISystemFunctions::ReplaceWidgetFromInstance(UObject* WorldContextObject, UUserWidget* NewWidget)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->ReplaceWidgetFromInstance(NewWidget);
	}

	return nullptr;
}

UUserWidget* UUISystemFunctions::PopWidget(UObject* WorldContextObject)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PopWidget();
	}

	return nullptr;
}

UUserWidget* UUISystemFunctions::GetActiveWidget(UObject* WorldContextObject)
{
	UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject);
	if(Subsystem)
	{
		return Subsystem->GetActiveWidget();
	}

	return nullptr;
}

UUIWorldSubsystem* UUISystemFunctions::GetWorldSubsystem(UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if(!GameInstance)
	{
		UE_LOG(LogUISystem, Error, TEXT("UUISystemBPLibrary::GetWorldSubsystem: GameInstance is nullptr!"));
		return nullptr;
	}
	
	UUIWorldSubsystem* Subsystem = WorldContextObject->GetWorld()->GetSubsystem<UUIWorldSubsystem>();
	
	return Subsystem;
}

