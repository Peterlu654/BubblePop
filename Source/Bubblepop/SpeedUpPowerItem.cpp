// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"

#include "SpeedUpPowerItem.h"

void ASpeedUpPowerItem::BeginPlay() {
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPickupItem");
	this->OnActorBeginOverlap.AddUnique(Delegate);
}

void ASpeedUpPowerItem::OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor == nullptr) {
		return;
	}
		
	auto character = Cast<ABubblepopCharacter>(OtherActor);
	if (character == nullptr) {
		return;
	}
	AtttachedCharacter = character;
	AtttachedCharacter->MultiplyWalkSpeed(Factor);
	Pickedup = true;
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ASpeedUpPowerItem::RestoreCharacterSpeed, Timeout, false);
	this->SetActorHiddenInGame(true);
}

void ASpeedUpPowerItem::RestoreCharacterSpeed() {
	AtttachedCharacter->RestoreDefaultWalkSpeed();
	DestroyItem();
}