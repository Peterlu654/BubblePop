// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "PlayerBubble.h"
#include "BubblepopCharacter.h"


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
	SetActorEnableCollision(true);
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnHitBubble");
	this->OnActorBeginOverlap.AddUnique(Delegate);
	
}

// Called every frame
void APlayerBubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerBubble::OnHitBubble(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor == nullptr) 
		return;
	auto c = Cast<ABubblepopCharacter>(OtherActor);
	if (c == nullptr) 
		return;
	auto p = this->GetOwner();
	auto castedP = Cast<ABubblepopCharacter>(p);
	if (castedP == nullptr) 
		return;

	if (p == c) {
		//When Bubble is created
		return;
	}
    PlayBubbleSound(BubblePoppedSound);

	castedP->PopBubble();
    
	c->AddScoreAfterPopping();
}

UAudioComponent* APlayerBubble::PlayBubbleSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    if (Sound)
    {
        //AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
        //UGameplayStatics::Sound
        UGameplayStatics::PlaySound2D(GetWorld(), Sound);
    }
    return AC;
}

