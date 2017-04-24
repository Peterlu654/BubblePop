// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "DoubleDamagePowerItem.h"

void ADoubleDamagePowerItem::BeginPlay() {
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPickupItem");
	this->OnActorBeginOverlap.AddUnique(Delegate);
}

void ADoubleDamagePowerItem::OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor == nullptr) {
		return;
	}

	auto character = Cast<ABubblepopCharacter>(OtherActor);
	if (character == nullptr) {
		return;
	}
	AtttachedCharacter = character;
	AtttachedCharacter->MultiplyWeaponDamage(Factor);
	Pickedup = true;
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ADoubleDamagePowerItem::RestoreCharacterDamage, Timeout, false);
	this->SetActorHiddenInGame(true);
}

void ADoubleDamagePowerItem::RestoreCharacterDamage() {
	AtttachedCharacter->RestoreDefaultWeaponDamage();
	DestroyItem();
}