// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "BubblepopGameMode.h"
#include "BubblepopCharacter.h"
#include "BubblepopHUD.h"

static bool PlayerLoaded = false;
static bool GameStarted = false;


ABubblepopGameMode::ABubblepopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    
    static ConstructorHelpers::FClassFinder<AHUD> BubblepopHUDBPClass(TEXT("/Game/Blueprints/BP_BubblepopHUD"));
    if (BubblepopHUDBPClass.Class != NULL)
    {
        HUDClass = BubblepopHUDBPClass.Class;
    }
    
    PrimaryActorTick.bCanEverTick = true;

}

void ABubblepopGameMode::BeginPlay()
{
    Super::BeginPlay();
    if (PlayerLoaded)
    {
        RemainingTime = 60;
        GameStarted = true;
    }
    else
    {
        UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
        PlayerLoaded = true;
    }

    
}

void ABubblepopGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RemainingTime -= DeltaTime;
    if (RemainingTime <= 0.0f && GameStarted)
    {
        //end game
        PlayerLoaded = false;
        GameStarted = false;
        FGenericPlatformMisc::RequestExit(false);

    }
}

bool ABubblepopGameMode::HasGameStarted()
{
    return GameStarted;
}
