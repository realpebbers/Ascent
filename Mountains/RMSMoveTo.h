// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/RootMotionSource.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RMSMoveTo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRootMotionFinished);

/**
 * 
 */
UCLASS()
class MOUNTAINS_API ARMSMoveTo : public AActor
{
	GENERATED_BODY()

	TSharedPtr<FRootMotionSource_MoveToForce> TransitionRMS;
	uint16 TransitionRMS_ID = 0;

	UPROPERTY(BlueprintAssignable)
	FOnRootMotionFinished OnRootMotionFinished;

	ACharacter* SavedCharacter = nullptr;
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveCharacterTo(ACharacter* Character, FVector Target, float MinTime = 0.1, float MaxTime = 0.2, float Dist = 500);
};
