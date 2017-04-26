// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "DamageResistancePowerItem.h"

void ADamageResistancePowerItem::BeginPlay() {
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPickupItem");
	this->OnActorBeginOverlap.AddUnique(Delegate);
}

void ADamageResistancePowerItem::OnPickupItem(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor == nullptr) {
		return;
	}

	auto character = Cast<ABubblepopCharacter>(OtherActor);
	if (character == nullptr) {
		return;
	}

	AtttachedCharacter = character;
	AtttachedCharacter->MultiplyDamageResistance(Factor);
	Pickedup = true;
    UGameplayStatics::PlaySound2D(GetWorld(), PickedUpSound);
    FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ADamageResistancePowerItem::RestoreCharacterDamageResistance, Timeout, false);
	this->SetActorHiddenInGame(true);
}

void ADamageResistancePowerItem::RestoreCharacterDamageResistance() {
	AtttachedCharacter->RestoreDefaultDamageResistance();
	DestroyItem();
}


