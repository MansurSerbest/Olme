#pragma once
#include "Engine/DataTable.h"
#include "OlmeStructs.generated.h"

USTRUCT(BlueprintType)
struct FPairIntName
{
	GENERATED_BODY()

	FPairIntName()
		:First(0), Second(TEXT("")){}
	
	FPairIntName(const int32 F, const FName& S)
		:First(F), Second(S){}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 First;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Second;
};

USTRUCT(BlueprintType)
struct FLevelData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};

USTRUCT(BlueprintType)
struct FChampionData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DisplayModelActor;
};

USTRUCT(BlueprintType)
struct FLobbyPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReady{false};
};

USTRUCT(BlueprintType)
struct FLobbyGameTypeData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinNrOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxNrOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Maps;
};
