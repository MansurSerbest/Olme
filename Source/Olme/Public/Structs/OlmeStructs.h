#pragma once
#include "Engine/DataTable.h"
#include "OlmeStructs.generated.h"

USTRUCT(BlueprintType)
struct FLevelData : public FTableRowBase
{
	GENERATED_BODY()
 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};