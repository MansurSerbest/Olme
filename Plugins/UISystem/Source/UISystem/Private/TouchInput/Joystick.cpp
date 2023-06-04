// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchInput/Joystick.h"

UJoystick::UJoystick(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//SetConsumePointerInput(true);
}

FReply UJoystick::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchStarted(InGeometry, InGestureEvent);
	
	TouchOrigin = InGestureEvent.GetScreenSpacePosition();

	FReply Reply = FReply::Handled();
	if (!HasMouseCaptureByUser(InGestureEvent.GetUserIndex(), InGestureEvent.GetPointerIndex()))
	{
		Reply.CaptureMouse(GetCachedWidget().ToSharedRef());
	}
	return Reply;
}

FReply UJoystick::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchMoved(InGeometry, InGestureEvent);
	HandleTouchDelta(InGeometry, InGestureEvent);

	FReply Reply = FReply::Handled();
	if (!HasMouseCaptureByUser(InGestureEvent.GetUserIndex(), InGestureEvent.GetPointerIndex()))
	{
		Reply.CaptureMouse(GetCachedWidget().ToSharedRef());
	}
	return Reply;
}

FReply UJoystick::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	StopInputSimulation();
	return FReply::Handled().ReleaseMouseCapture();
}

void UJoystick::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	StopInputSimulation();
}

void UJoystick::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// Move the inner stick icon around with the vector
	if (JoystickForeground && JoystickBackground)
	{
		JoystickForeground->SetRenderTranslation(
			(bNegateYAxis ? FVector2D(1.0f, -1.0f) : FVector2D(1.0f)) *
			StickVector *
			(JoystickBackground->GetDesiredSize() * 0.5f)
		);
	}
}

void UJoystick::HandleTouchDelta(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	const FVector2D& ScreenSpacePos = InGestureEvent.GetScreenSpacePosition();
	
	// The center of the geo locally is just its size
	FVector2D LocalStickCenter = InGeometry.GetAbsoluteSize();

	FVector2D ScreenSpaceStickCenter = InGeometry.LocalToAbsolute(LocalStickCenter);
	// Get the offset from the origin
	FVector2D MoveStickOffset = (ScreenSpacePos - ScreenSpaceStickCenter);
	if (bNegateYAxis)
	{
		MoveStickOffset *= FVector2D(1.0f, -1.0f);
	}
	
	FVector2D MoveStickDir = FVector2D::ZeroVector;
	float MoveStickLength = 0.0f;
	MoveStickOffset.ToDirectionAndLength(MoveStickDir, MoveStickLength);

	MoveStickLength = FMath::Min(MoveStickLength, StickRange);
	MoveStickOffset = MoveStickDir * MoveStickLength;

	StickVector = MoveStickOffset / StickRange;

	UE_LOG(LogTemp, Warning, TEXT("StickVector: %s"), *StickVector.ToString());
}

void UJoystick::StopInputSimulation()
{
	TouchOrigin = FVector2D::ZeroVector;
	StickVector = FVector2D::ZeroVector;
}
