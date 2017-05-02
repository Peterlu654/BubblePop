// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerItem.h"
#include "HealthPackPowerItem.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API AHealthPackPowerItem : public APowerItem
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Effect)
	int HealthPoint;


private:
	UFUNCTION()
	void OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//const int HealthPoint = 50;

	
};
