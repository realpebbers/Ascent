// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HandConstraintComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtendedMax, FVector, Force);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOUNTAINS_API UHandConstraintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandConstraintComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnExtendedMax OnExtendedMax;

	UPROPERTY()
	UPrimitiveComponent* Unmovable;

	UPROPERTY()
	UPrimitiveComponent* Movable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget))
	FVector AnchorOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector UnmovableOffset;
	
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* VelocityComp;

	UPROPERTY()
	ACharacter* MovableCharacter;

	UPROPERTY(EditAnywhere)
	bool bOnlyIfBiggerDistance = false;

	UPROPERTY(EditAnywhere)
	float BiasFactor = 0.01f;
	
	float Distance = 0.f;

	UPROPERTY(EditAnywhere)
	float MinDistance = 0.f;

	UPROPERTY(EditAnywhere)
	float PlayerMass = 99.999992;
	
	float InverseMass1;
	float InverseMass2;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateConstraint(float dt);

	UFUNCTION(BlueprintCallable)
	void SetConstraint(UPrimitiveComponent* InUnmovable, UPrimitiveComponent* InMovable, float MaxDistance);

	UFUNCTION(BlueprintCallable)
	void SetPlayer(UPrimitiveComponent* InUnmovable, ACharacter* Character, float MaxDistance);

	UFUNCTION(BlueprintCallable)
	void StopConstraint();
};
