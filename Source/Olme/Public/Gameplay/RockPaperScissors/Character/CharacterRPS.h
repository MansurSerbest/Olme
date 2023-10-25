// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/RockPaperScissors/RPSStructs.h"
#include "CharacterRPS.generated.h"

class UWidgetComponent;
class UInputMappingContext;
struct FInputActionInstance;

UCLASS()
class OLME_API ACharacterRPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterRPS();

	UFUNCTION(Server, Reliable)
	void SetChoice_Server(const ERockPaperScissors NewChoice);

	void SetCharacterName(const FString& Name);

	void SetScore(const float NewScore);

	static ACharacterRPS* ResolveWinner(ACharacterRPS* PlayerOne, ACharacterRPS* PlayerTwo);

	void SetCheckBoxes(const bool bVisible);

	UFUNCTION(NetMulticast, Reliable)
	void StartRound();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Choose(const FInputActionInstance& Action);

	void Confirm(const FInputActionInstance& Action);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(Replicated)
	ERockPaperScissors Choice;
};
