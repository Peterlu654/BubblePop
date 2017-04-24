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
	int NumSpawnPoints = SpawnPoints.Num();
	if (NumSpawnPoints == 0) return;

	int TargetIndex = FMath::RandRange(0, NumSpawnPoints - 1);

	ATargetPoint* point = SpawnPoints[TargetIndex];
	const FVector pos = point->GetActorLocation();
	const FRotator rot = point->GetActorRotation();

	int NumPowerItemClasses = PowerItemClasses.Num();
	int ClassIndex = FMath::RandRange(0, NumPowerItemClasses-1);

	TSubclassOf<APowerItem> PowerItemClass = PowerItemClasses[ClassIndex];
	APowerItem* item = GetWorld()->SpawnActor<APowerItem>((UClass*)PowerItemClass, pos, rot);
}

