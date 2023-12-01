// Fill out your copyright notice in the Description page of Project Settings.


#include "HandConstraintComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UHandConstraintComponent::UHandConstraintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHandConstraintComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHandConstraintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((IsValid( MovableCharacter) || IsValid(Movable)) && IsValid(Unmovable))
	{
		// 10 is const, constraintIterationCount
		float ConstraintDeltaTime = DeltaTime / 10;

		for (int i = 0; i < 10; ++i)
		{
			UpdateConstraint(ConstraintDeltaTime);
		}
	}
}

void UHandConstraintComponent::UpdateConstraint(float dt)
{
	bool bIsPlayer = IsValid(MovableCharacter);

	UPrimitiveComponent* MovablePrimitive = bIsPlayer ? MovableCharacter->GetCapsuleComponent() : Movable;

	const FVector OffsetVec = Unmovable->GetComponentLocation() - (MovablePrimitive->GetComponentLocation() + AnchorOffset);
	const float CurrentDistance = FVector::Distance(Unmovable->GetComponentLocation() + UnmovableOffset, (MovablePrimitive->GetComponentLocation() + AnchorOffset));

	if (bOnlyIfBiggerDistance && (CurrentDistance < Distance)) return;

	
	if (const float Offset = Distance - CurrentDistance; FMath::Abs(Offset) > 0.f)
	{
		const FVector OffsetDir = OffsetVec.GetSafeNormal();
		const FVector RelativeVel = Unmovable->GetPhysicsLinearVelocity() - MovablePrimitive->GetPhysicsLinearVelocity();
		const float ConstraintMass = InverseMass1 + InverseMass2;

		if (ConstraintMass > 0.0f)
		{
			const float VelocityDot = RelativeVel.Dot(OffsetDir);
			const float Bias = -(BiasFactor / dt) * Offset;
			const float Lambda = -(VelocityDot + Bias) / ConstraintMass;

			FVector Impulse2 = -OffsetDir * Lambda;

			// Unmovable->AddForce(Impulse1);
			if (IsValid(MovableCharacter))
			{
				MovableCharacter->GetCharacterMovement()->AddForce(Impulse2);
				if (bOnlyIfBiggerDistance) OnExtendedMax.Broadcast(Impulse2);
			}
			else
			{
				Movable->AddForce(Impulse2);
			}
		}
	}
}

void UHandConstraintComponent::SetConstraint(UPrimitiveComponent* InUnmovable, UPrimitiveComponent* InMovable, float MaxDistance)
{
	Unmovable = InUnmovable;
	Movable = InMovable;

	Distance = MaxDistance;
	InverseMass1 = 0;
	InverseMass2 = 1/Movable->GetMass();
}

void UHandConstraintComponent::SetPlayer(UPrimitiveComponent* InUnmovable, ACharacter* Character, float MaxDistance)
{
	Unmovable = InUnmovable;
	MovableCharacter = Character;	
	
	Distance = MaxDistance;
	InverseMass1 = 0;
	InverseMass2 = 1/PlayerMass;
}

void UHandConstraintComponent::StopConstraint()
{
	Unmovable = nullptr;
	Movable = nullptr;
	MovableCharacter = nullptr;
}

