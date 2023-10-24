// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"

#include "EnhancedInputComponent.h"
#include "Algo/Rotate.h"
#include "Camera/CameraActor.h"
#include "Components/WidgetComponent.h"
#include "Gameplay/RockPaperScissors/Input/RPSInputDataAsset.h"
#include "Gameplay/RockPaperScissors/UI/WidgetRPSCharacter.h"
#include "HelperFunctions/OlmeHelperFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Olme/Olme.h"


// Sets default values
ACharacterRPS::ACharacterRPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetComponent")));
	if(WidgetComponent)
	{
		WidgetComponent->SetupAttachment(GetRootComponent());
		WidgetComponent->SetCastShadow(false); // We don't need shadow for this
	}
}

void ACharacterRPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterRPS, Choice);
}

// Called when the game starts or when spawned
void ACharacterRPS::BeginPlay()
{
	Super::BeginPlay();

	// Set the rotation of the widget component
	if(const AActor* Camera = UGameplayStatics::GetActorOfClass(this, ACameraActor::StaticClass()))
	{
		const FVector Direction = Camera->GetActorLocation() - WidgetComponent->GetComponentLocation();
		const FRotator newRotation = Direction.Rotation();

		WidgetComponent->SetWorldRotation(newRotation);
	}

	// Set the choice of the other player to unknown
	if(!UOlmeHelperFunctions::IsPawnLocallyOwned(this))
	{
		if(UWidgetRPSCharacter* Widget = Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget()))
		{
			Widget->SetChoice(ERockPaperScissors::eMax);
		}
	}
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
	const float value = Action.GetValue().Get<float>();
	const int32 currChoice = static_cast<int8>(Choice);
	int32 result = UOlmeHelperFunctions::ShiftInRotation(static_cast<int32>(ERockPaperScissors::eMax), value, currChoice);

	Choice = static_cast<ERockPaperScissors>(result);
	UE_LOG(LogOlme, Warning, TEXT("NEW CHOICE %d"), result);

	if(WidgetComponent)
	{
		UWidgetRPSCharacter* Widget =  Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget());
		Widget->SetChoice(Choice);
	}
}


