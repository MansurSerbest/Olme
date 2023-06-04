// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UIWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UISYSTEM_API UUIWorldSubsystem : public UWorldSubsystem 
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void PostInitialize() override;
	
	//These functions push a new widget to the stack, still remember the last widget in the stack
	UUserWidget* PushWidgetFromClass(const TSubclassOf<UUserWidget>& Class, bool bPreviousWidgetVisible = false);
	UUserWidget* PushWidgetFromInstance(UUserWidget* NewWidget, bool bPreviousWidgetVisible = false);

	//These functions replace widget on the top of the stack with a new widget
	UUserWidget* ReplaceWidgetFromClass(const TSubclassOf<UUserWidget>& Class, bool bReplaceWholeStack = false);
	UUserWidget* ReplaceWidgetFromInstance(UUserWidget* NewWidget, bool bReplaceWholeStack = false);

	//These functions pop widget
	UUserWidget* PopWidget();

private:
	UPROPERTY()
	TArray<UUserWidget*> WidgetStack;
};
