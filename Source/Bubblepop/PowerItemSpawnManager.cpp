// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "SpeedUpPowerItem.h"
#include "PowerItemSpawnManager.h"


// Sets default values
APowerItemSpawnManager::APowerItemSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnTime = 5.0f;
}

// Called when the game starts or when spawned
void APowerItemSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &APowerItemSpawnManager::OnSpawnPowerItem, SpawnTime, true);
}

// Called every frame
void APowerItemSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerItemSpawnManager::OnSpawnPowerItem()
{
	int num = SpawnPoints.Num();
	if (num == 0) return;

	int index = FMath::RandRange(0, num - 1);

	ATargetPoint* point = SpawnPoints[index];
	FVector pos = point->GetActorLocation();
	FRotator rot = point->GetActorRotation();

	//GetWorld()->SpawnActor<ASpeedUpPowerItem>(PowerItemClass, pos, rot);
}

