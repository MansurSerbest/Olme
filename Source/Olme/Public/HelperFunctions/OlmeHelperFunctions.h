// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OlmeHelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class OLME_API UOlmeHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void PrintNetMode(const UObject* WorldContextObject, const FString& Text);
};
