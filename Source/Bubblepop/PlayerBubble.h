// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerBubble.generated.h"

UCLASS()
class BUBBLEPOP_API APlayerBubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBubble();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* BubblePoppedSound;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* BecomingBubbleSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHitBubble(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
    
    // For playing sounds
    UAudioComponent* PlayBubbleSound(USoundCue*);
	
};
