// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerItem.h"
#include "BonusScorePowerItem.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API ABonusScorePowerItem : public APowerItem
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void RestoreBonusScore();

	const int Factor = 10;

	const float Timeout = 20.0f;
	
};
