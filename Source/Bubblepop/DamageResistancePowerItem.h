// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerItem.h"
#include "DamageResistancePowerItem.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API ADamageResistancePowerItem : public APowerItem
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void RestoreCharacterDamageResistance();

	const float Factor = 2.0f;

	const float Timeout = 5.0f;
};
