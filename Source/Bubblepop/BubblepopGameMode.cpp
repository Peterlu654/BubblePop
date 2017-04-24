// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "BubblepopGameMode.h"
#include "BubblepopCharacter.h"
#include "BubblepopHUD.h"
#include <iostream>

static bool GameStarted = false;
static int ModeNum = 0;

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
    MyModeNum = ModeNum;
    ModeNum++;

}

void ABubblepopGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    if (MyModeNum == 0)
    {
        return;
    }
    
    // Need to respawn another player
    else if (GetNumPlayers() == 1)
    {
        UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
        GameStarted = true;
        RemainingTime = 60.0f;
        
    }
    else
    {
        GameStarted = true;
        RemainingTime = 60.0f;
    }
    
}

void ABubblepopGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!GameStarted)
    {
        return;
    }
    RemainingTime -= DeltaTime;
    if (RemainingTime <= 0.0f)
    {
        //end game
        GameStarted = false;
        UGameplayStatics::OpenLevel(GetWorld(), "/Game/ThirdPersonCPP/Maps/MainMenu");
    }
}

bool ABubblepopGameMode::HasGameStarted()
{
    return GameStarted;
}

void ABubblepopGameMode::BeginDestroy()
{
    Super::BeginDestroy();
    
    if (MyModeNum == 0)
    {
        return;
    }
    
    GameStarted = false;
}
