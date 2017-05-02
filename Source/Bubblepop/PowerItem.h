// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BubblepopCharacter.h"
#include "PowerItem.generated.h"

UCLASS()
class BUBBLEPOP_API APowerItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ABubblepopCharacter* AtttachedCharacter;
	bool Pickedup;

	void DestroyItem();
    
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* PickedUpSound;

	UPROPERTY(EditDefaultsOnly)
	float DisappearTimeout;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	//const float DisappearTimeout = 15.0f;

	
	
};
