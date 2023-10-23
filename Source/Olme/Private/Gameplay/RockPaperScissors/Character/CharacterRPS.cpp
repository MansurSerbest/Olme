// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"

#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"
#include "Gameplay/RockPaperScissors/Input/RPSInputDataAsset.h"
#include "Olme/Olme.h"


// Sets default values
ACharacterRPS::ACharacterRPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetComponent")));
}

// Called when the game starts or when spawned
void ACharacterRPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterRPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterRPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const URPSInputDataAsset* InputActions = NewObject<URPSInputDataAsset>();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if(EnhancedInputComponent && InputActions)
	{
		EnhancedInputComponent->BindAction(InputActions->Choose, ETriggerEvent::Triggered, this, &ACharacterRPS::Choose);
	}
}

void ACharacterRPS::Choose(const FInputActionInstance& Action)
{
	UE_LOG(LogOlme, Warning, TEXT("ACharacterRPS::Choose(const FInputActionInstance& Action)"));
}

