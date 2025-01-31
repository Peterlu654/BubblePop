// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "HealthPackPowerItem.h"


void AHealthPackPowerItem::BeginPlay() {
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPickupItem");
	this->OnActorBeginOverlap.AddUnique(Delegate);
}

void AHealthPackPowerItem::OnPickupItem(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor == nullptr) {
		return;
	}

	auto character = Cast<ABubblepopCharacter>(OtherActor);
	if (character == nullptr) {
		return;
	}
	AtttachedCharacter = character;
	AtttachedCharacter->IncreaseCharacterHealth(HealthPoint);
	Pickedup = true;
    UGameplayStatics::PlaySound2D(GetWorld(), PickedUpSound);
    this->SetActorHiddenInGame(true);
	DestroyItem();
}

