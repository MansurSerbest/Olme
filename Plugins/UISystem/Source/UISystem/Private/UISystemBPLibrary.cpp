// Copyright Epic Games, Inc. All Rights Reserved.

#include "UISystemBPLibrary.h"
#include "UISystem.h"
#include "Kismet/GameplayStatics.h"
#include "UIWorldSubsystem.h"

UUISystemBPLibrary::UUISystemBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UUserWidget* UUISystemBPLibrary::PushWidgetFromClass(UObject* WorldContextObject, TSubclassOf<UUserWidget> Class, bool bPreviousWidgetVisible)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PushWidgetFromClass(Class, bPreviousWidgetVisible);
	}

	return nullptr;
}

UUserWidget* UUISystemBPLibrary::PushWidgetFromInstance(UObject* WorldContextObject, UUserWidget* NewWidget, bool bPreviousWidgetVisible)
{
	if(UUIWorldSubsystem* Subsystem = UUISystemBPLibrary::GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PushWidgetFromInstance(NewWidget, bPreviousWidgetVisible);
	}

	return nullptr;
}

UUserWidget* UUISystemBPLibrary::ReplaceWidgetFromClass(UObject* WorldContextObject, TSubclassOf<UUserWidget> Class)
{
	if(UUIWorldSubsystem* Subsystem = UUISystemBPLibrary::GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->ReplaceWidgetFromClass(Class);
	}

	return nullptr;
}

UUserWidget* UUISystemBPLibrary::ReplaceWidgetFromInstance(UObject* WorldContextObject, UUserWidget* NewWidget)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->ReplaceWidgetFromInstance(NewWidget);
	}

	return nullptr;
}

UUserWidget* UUISystemBPLibrary::PopWidget(UObject* WorldContextObject)
{
	if(UUIWorldSubsystem* Subsystem = GetWorldSubsystem(WorldContextObject))
	{
		return Subsystem->PopWidget();
	}

	return nullptr;
}

UUIWorldSubsystem* UUISystemBPLibrary::GetWorldSubsystem(UObject* WorldContextObject)
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

