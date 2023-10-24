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

	// Makes sure that after the shift of the idx value, the idx value will stay between [0, Size[
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static int32 ShiftInRotation(const int Size, const int Direction, int Idx);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool IsPawnLocallyOwned(const APawn* Pawn);
};
