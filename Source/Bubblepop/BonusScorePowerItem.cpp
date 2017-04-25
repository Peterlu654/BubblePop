// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "BonusScorePowerItem.h"

void ABonusScorePowerItem::BeginPlay() {
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPickupItem");
	this->OnActorBeginOverlap.AddUnique(Delegate);
}

void ABonusScorePowerItem::OnPickupItem(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor == nullptr) {
		return;
	}

	auto character = Cast<ABubblepopCharacter>(OtherActor);
	if (character == nullptr) {
		return;
	}
	AtttachedCharacter = character;
	AtttachedCharacter->IncreasePopScore(Factor);
	Pickedup = true;
    UGameplayStatics::PlaySound2D(GetWorld(), PickedUpSound);
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ABonusScorePowerItem::RestoreBonusScore, Timeout, false);
	this->SetActorHiddenInGame(true);
}

void ABonusScorePowerItem::RestoreBonusScore()
{
	AtttachedCharacter->RestoreDefaultPopScore();
	DestroyItem();
}
