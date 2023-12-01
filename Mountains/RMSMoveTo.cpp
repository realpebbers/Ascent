// Fill out your copyright notice in the Description page of Project Settings.


#include "RMSMoveTo.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ARMSMoveTo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(SavedCharacter))
	{
		TSharedPtr<FRootMotionSource> MTF = SavedCharacter->GetCharacterMovement()->GetRootMotionSourceByID(TransitionRMS_ID);
		if (MTF && MTF->Status.HasFlag(ERootMotionSourceStatusFlags::Finished))
		{
			SavedCharacter->GetCharacterMovement()->RemoveRootMotionSourceByID(TransitionRMS_ID);
			OnRootMotionFinished.Broadcast();
		}
	}
}

void ARMSMoveTo::MoveCharacterTo(ACharacter* Character, FVector Target, float MinTime, float MaxTime, float Dist)
{
	UCapsuleComponent* Component = Character->GetCapsuleComponent();
	UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
	const float TransDistance = FVector::Dist(Component->GetComponentLocation(), Target);

	TransitionRMS.Reset();
	TransitionRMS = MakeShared<FRootMotionSource_MoveToForce>();
	TransitionRMS->AccumulateMode = ERootMotionAccumulateMode::Override;
	TransitionRMS->Duration = FMath::Clamp(TransDistance / Dist, MinTime, MaxTime);

	TransitionRMS->StartLocation = Component->GetComponentLocation();
	TransitionRMS->TargetLocation = Target;

	Movement->Velocity = FVector::ZeroVector;
	Movement->SetMovementMode(MOVE_Flying);
	TransitionRMS_ID = Movement->ApplyRootMotionSource(TransitionRMS);

	SavedCharacter = Character;
}
