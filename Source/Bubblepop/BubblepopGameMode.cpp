// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "BubblepopGameMode.h"
#include "BubblepopCharacter.h"

static bool PlayerLoaded = false;


ABubblepopGameMode::ABubblepopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABubblepopGameMode::BeginPlay()
{
    if (!PlayerLoaded)
    {
        UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
        PlayerLoaded = true;
    }
}
