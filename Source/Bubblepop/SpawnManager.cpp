// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "SpawnManager.h"
#include "Engine/TargetPoint.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
    OnSpawnTimer();
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASpawnManager::OnSpawnTimer()
{
    
    int numSpawn = SpawnPoints.Num();
    int index = FMath::RandRange(0, numSpawn - 1);
    ATargetPoint* point = SpawnPoints[index];
    FVector pos = point->GetActorLocation();
    FRotator rot = point->GetActorRotation();
    ACharacter* Char = GetWorld()->SpawnActor<ACharacter>(CharacterClass, pos, rot);
    
    //UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
}
