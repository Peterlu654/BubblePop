// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerItem.h"
#include "DoubleDamagePowerItem.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API ADoubleDamagePowerItem : public APowerItem
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void RestoreCharacterDamage();

	const float Factor = 2.0f;

	const float Timeout = 5.0f;
	
	
};
