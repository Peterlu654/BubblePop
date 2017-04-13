// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class BUBBLEPOP_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();
    
    void OnSpawnTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere)
    TArray<class ATargetPoint*> SpawnPoints;
    

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
