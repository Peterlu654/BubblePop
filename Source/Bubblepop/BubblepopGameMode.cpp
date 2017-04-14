// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "BubblepopGameMode.h"
#include "BubblepopCharacter.h"
#include "BubblepopHUD.h"

static bool PlayerLoaded = false;
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
    else
    {
        ModeNum = 1;
        UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
        GameStarted = true;
        RemainingTime = 60.0f;
        
    }
    
    
    /*if (PlayerLoaded)
    {
        RemainingTime = 10;
        GameStarted = true;
    }
    else
    {
        UGameplayStatics::CreatePlayer(GetWorld(),-1, true);
        PlayerLoaded = true;

    }*/

    
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
        PlayerLoaded = false;
        GameStarted = false;
//        FGenericPlatformMisc::RequestExit(false);
        //auto PlayerOneCharacter = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
        //PlayerOneCharacter->GetController()->ConsoleCommand("quit");
        //GetWorld()->Exec(GetWorld(), TEXT("exit"));
        UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit);


    }
}

bool ABubblepopGameMode::HasGameStarted()
{
    return GameStarted;
}

/*void ABubblepopGameMode::BeginDestroy()
{
    PlayerLoaded = false;
    GameStarted = false;
    PrimaryActorTick.bCanEverTick = false;
}*/

void ABubblepopGameMode::BeginDestroy()
{
    Super::BeginDestroy();
    
    if (MyModeNum == 0)
    {
        return;
    }
    GameStarted = false;
    //if (PlayerLoaded == true && GameStarted == true)
    /*{
        PlayerLoaded = false;

    }
    GameStarted = false;*/
    
}







