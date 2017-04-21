// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PowerItem.h"
#include "PowerItemSpawnManager.generated.h"

UCLASS()
class BUBBLEPOP_API APowerItemSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerItemSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APowerItem>> PowerItemClasses;

	UPROPERTY(EditAnywhere)
	float SpawnTime;

	void OnSpawnPowerItem();
	
};
