// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWorldSubsystem.h"

#include "UISystem.h"
#include "Blueprint/UserWidget.h"


void UUIWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UUIWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

UUserWidget* UUIWorldSubsystem::PushWidgetFromClass(const TSubclassOf<UUserWidget>& Class, bool bPreviousWidgetVisible)
{
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorldRef().GetFirstPlayerController(), Class);
	return PushWidgetFromInstance(widget, bPreviousWidgetVisible);
}

UUserWidget* UUIWorldSubsystem::PushWidgetFromInstance(UUserWidget* NewWidget, bool bPreviousWidgetVisible)
{
	if(NewWidget == nullptr)
	{
		UE_LOG(LogUISystem, Warning, TEXT("UUIGameInstanceSubsystem::CreateWidgetFromInstance: Widget is nullptr!"));
		return nullptr;
	}

	if(WidgetStack.IsValidIndex(0))
	{
		if(UUserWidget* LastWidget = WidgetStack.Last())
		{
			if(!bPreviousWidgetVisible)
			{
				LastWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}

	WidgetStack.Push(NewWidget);
	NewWidget->AddToViewport();

	return NewWidget;
}

UUserWidget* UUIWorldSubsystem::ReplaceWidgetFromClass(const TSubclassOf<UUserWidget>& Class, bool bReplaceWholeStack )
{
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorldRef().GetFirstPlayerController(), Class);
	return ReplaceWidgetFromInstance(widget, bReplaceWholeStack);
}

UUserWidget* UUIWorldSubsystem::ReplaceWidgetFromInstance(UUserWidget* NewWidget, bool bReplaceWholeStack)
{
	if(NewWidget == nullptr)
	{
		UE_LOG(LogUISystem, Warning, TEXT("UUIGameInstanceSubsystem::ReplaceWidgetFromInstance: Widget is nullptr!"));
		return nullptr;
	}

	if(bReplaceWholeStack)
	{
		for(UUserWidget* WidgetToRemove : WidgetStack)
		{
			WidgetToRemove->RemoveFromParent();
		}
		WidgetStack.Empty();
	}
	else if(WidgetStack.IsValidIndex(0))
	{
		UUserWidget* WidgetToRemove = WidgetStack.Pop();
		if(WidgetToRemove)
		{
			WidgetToRemove->RemoveFromParent();
		}
	}
	WidgetStack.Push(NewWidget);
	NewWidget->AddToViewport();
	return NewWidget;
}

UUserWidget* UUIWorldSubsystem::PopWidget()
{
	if(WidgetStack.IsValidIndex(0))
	{
		if(UUserWidget* RemovedWidget = WidgetStack.Pop())
		{
			RemovedWidget->RemoveFromParent();
		}
		
		if(WidgetStack.IsValidIndex(0))
		{
			WidgetStack.Last()->SetVisibility(ESlateVisibility::Visible);
		}
	}

	return nullptr;
}

UUserWidget* UUIWorldSubsystem::GetActiveWidget()
{
	if(WidgetStack.IsValidIndex(0))
	{
		return WidgetStack.Last(); 
	}

	return nullptr;
}
