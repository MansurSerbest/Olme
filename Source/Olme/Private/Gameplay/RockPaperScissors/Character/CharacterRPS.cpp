// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RockPaperScissors/Character/CharacterRPS.h"

#include "EnhancedInputComponent.h"
#include "Algo/Rotate.h"
#include "Base/RPS/GameStateRPS.h"
#include "Base/RPS/PlayerStateRPS.h"
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

void ACharacterRPS::SetChoice_Server_Implementation(const ERockPaperScissors NewChoice)
{
	Choice = NewChoice;
}

void ACharacterRPS::SetCharacterName(const FString& Name)
{
	if(UWidgetRPSCharacter* Widget = Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget()))
	{
		Widget->SetName(Name);
	}
}

void ACharacterRPS::SetScore(const float NewScore)
{
	if(UWidgetRPSCharacter* Widget = Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget()))
	{
		Widget->SetScore(NewScore);
	}
}

ACharacterRPS* ACharacterRPS::ResolveWinner(ACharacterRPS* PlayerOne, ACharacterRPS* PlayerTwo)
{
	// Check draw
	if(PlayerOne->Choice == PlayerTwo->Choice)
	{
		return nullptr;
	}

	// Check against rock
	if(PlayerOne->Choice == ERockPaperScissors::eRock)
	{
		if(PlayerTwo->Choice == ERockPaperScissors::eScissors)
		{
			return PlayerOne;
		}

		return PlayerTwo;
	}

	// Check against paper
	if(PlayerOne->Choice == ERockPaperScissors::ePaper)
	{
		if(PlayerTwo->Choice == ERockPaperScissors::eRock)
		{
			return PlayerOne;
		}

		return PlayerTwo;
	}

	
	// Check against scissors
	if(PlayerOne->Choice == ERockPaperScissors::eScissors)
	{
		if(PlayerTwo->Choice == ERockPaperScissors::ePaper)
		{
			return PlayerOne;
		}

		return PlayerTwo;
	}

	return nullptr;
}

void ACharacterRPS::SetCheckBoxes(const bool bVisible)
{
	if(WidgetComponent)
	{
		UWidgetRPSCharacter* Widget =  Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget());
		if(Widget)
		{
			Widget->SetCheckbox(bVisible);
		}
	}
}

void ACharacterRPS::StartRound_Implementation()
{
	if(!WidgetComponent)
	{
		return;
	}
	Choice = ERockPaperScissors::eRock;
	if(UWidgetRPSCharacter* Widget = Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget()))
	{
		if(UOlmeHelperFunctions::IsPawnLocallyOwned(this))
		{
			Widget->SetChoice(ERockPaperScissors::eRock);
		}
		else
		{
			Widget->SetChoice(ERockPaperScissors::eMax);
		}
	}
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

	if(UWidgetRPSCharacter* Widget = Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget()))
	{
		// Set the choice of the other player to unknown
		if(!UOlmeHelperFunctions::IsPawnLocallyOwned(this))
		{
			Widget->SetChoice(ERockPaperScissors::eMax);
		}

		// Set the name of the player
		if(const APlayerStateRPS* PS = Cast<APlayerStateRPS>(GetPlayerState()))
		{
			Widget->SetName(PS->GetCustomName());
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
		EnhancedInputComponent->BindAction(InputActions->ConfirmChoice, ETriggerEvent::Triggered, this, &ACharacterRPS::Confirm);
	}
}

void ACharacterRPS::Choose(const FInputActionInstance& Action)
{
	AGameStateRPS* GS = Cast<AGameStateRPS>( UGameplayStatics::GetGameState(this));
	if(!GS)
	{
		return;
	}

	if(GS->GetMatchStarted())
	{
		const float value = Action.GetValue().Get<float>();
		const int32 currChoice = static_cast<int8>(Choice);
		int32 result = UOlmeHelperFunctions::ShiftInRotation(static_cast<int32>(ERockPaperScissors::eMax), value, currChoice);
		Choice = static_cast<ERockPaperScissors>(result);
	
		if(WidgetComponent)
		{
			UWidgetRPSCharacter* Widget =  Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget());
			Widget->SetChoice(Choice);
		}

		// Send this result to the server and set it there too. From there, the variable will be replicated to all the other clients
		SetChoice_Server(Choice);
	}
}

void ACharacterRPS::Confirm(const FInputActionInstance& Action)
{
	AGameStateRPS* GS = Cast<AGameStateRPS>( UGameplayStatics::GetGameState(this));
	if(GS && GS->GetMatchStarted())
	{
		return;
	}
	
	if(APlayerStateRPS* PS = Cast<APlayerStateRPS>(GetPlayerState()))
	{
		PS->ToggleIsReady_Server();

		if(WidgetComponent && GetNetMode() == NM_Client)
		{
			UWidgetRPSCharacter* Widget =  Cast<UWidgetRPSCharacter>(WidgetComponent->GetWidget());
			Widget->SetCheckbox(!PS->GetIsReady());
		}
	}
}


