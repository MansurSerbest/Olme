// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPS/CharacterRPS.h"

// Sets default values
ACharacterRPS::ACharacterRPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}
