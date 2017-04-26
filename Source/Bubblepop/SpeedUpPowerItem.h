// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerItem.h"
#include "SpeedUpPowerItem.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API ASpeedUpPowerItem : public APowerItem
{
	GENERATED_BODY()
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	void RestoreCharacterSpeed();

	const float Factor = 2.0f;

	const float Timeout = 20.0f;

};
