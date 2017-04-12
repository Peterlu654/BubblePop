// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "PlayerBubble.h"


// Sets default values
APlayerBubble::APlayerBubble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBubble::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

