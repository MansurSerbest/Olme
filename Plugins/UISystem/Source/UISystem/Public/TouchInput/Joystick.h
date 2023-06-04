// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Joystick.generated.h"

/**
 * Simulate a joystick on a touchscreen that will give back an axis value between [-1, 1]
 */
UCLASS()
class UISYSTEM_API UJoystick : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UJoystick(const FObjectInitializer& ObjectInitializer);

	//~ Begin UUserWidget
	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//~ End UUserWidget interface
	
	protected:

	/**
	 * Calculate the delta position of the current touch from the origin.
	 *
	 * Input the associated gamepad key on the player
	 *
	 * Move the foreground joystick image in association with the given input to give the appearance that it
	 * is moving along with the player's finger
	 */
	void HandleTouchDelta(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent);
	
	/** Flush any player input that has been injected and disable the use of this analog stick. */
	void StopInputSimulation();

	/** How far can the inner image of the joystick be moved? */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float StickRange = 50.0f;

	/** Image to be used as the background of the joystick */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> JoystickBackground;

	/** Image to be used as the foreground of the joystick */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> JoystickForeground;

	/** Should we negate the Y-axis value of the joystick? This is common for "movement" sticks */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bNegateYAxis = false;

	/** The origin of the touch. Set on NativeOnTouchStarted */
	UPROPERTY(Transient)
	FVector2D TouchOrigin = FVector2D::ZeroVector;
 
	UPROPERTY(Transient)
	FVector2D StickVector = FVector2D::ZeroVector;
};
