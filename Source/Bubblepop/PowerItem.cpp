// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "PowerItem.h"


// Sets default values
APowerItem::APowerItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerItem::BeginPlay()
{
	Super::BeginPlay();
	/*
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "EffectDelegate");
	this->OnActorBeginOverlap.AddUnique(Delegate);
	*/
}

// Called every frame
void APowerItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

