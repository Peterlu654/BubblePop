// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "BubblepopGameMode.h"
#include "BubblepopCharacter.h"
#include "BubblepopHUD.h"
#include "BubblepopGameInstance.h"
#include "Weapon1.h"
#include "Weapon2.h"
#include "Weapon3.h"
#include "Character1.h"
#include "Character2.h"
#include "Character3.h"
#include <iostream>

static bool GameStarted = false;
static int ModeNum = 0;
static int PlayerOneScore = 0;
static int PlayerTwoScore = 0;
static TSubclassOf<APawn> Char1Class;
static TSubclassOf<APawn> Char2Class;
static TSubclassOf<APawn> Char3Class;


ABubblepopGameMode::ABubblepopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    
    static ConstructorHelpers::FClassFinder<APawn>Pawn1BPClass(TEXT("/Game/Blueprints/BP_Character1"));
    static ConstructorHelpers::FClassFinder<APawn>Pawn2BPClass(TEXT("/Game/Blueprints/BP_Character2"));
    static ConstructorHelpers::FClassFinder<APawn>Pawn3BPClass(TEXT("/Game/Blueprints/BP_Character3"));
                                                               
                                                               Char1Class = Pawn1BPClass.Class;
                                                               Char2Class = Pawn2BPClass.Class;
                                                               Char3Class = Pawn3BPClass.Class;
    
    
    static ConstructorHelpers::FClassFinder<AHUD> BubblepopHUDBPClass(TEXT("/Game/Blueprints/BP_BubblepopHUD"));
    if (BubblepopHUDBPClass.Class != NULL)
    {
        HUDClass = BubblepopHUDBPClass.Class;
    }
    PrimaryActorTick.bCanEverTick = true;
    MyModeNum = ModeNum;
    ModeNum++;
    if (MyModeNum == 0)
    {
        return;
    }
    

    
    /*FString PlayerOneClass = "/Game/Blueprints/" + PlayerOneChoice;
    FString PlayerTwoClass = "/Game/Blueprints/" + PlayerTwoChoice;
    
    static ConstructorHelpers::FClassFinder<APawn> PlayerOnePawnBPClass(*PlayerOneClass);
    static ConstructorHelpers::FClassFinder<APawn> PlayerTwoPawnBPClass(*PlayerTwoClass);
    
    if (PlayerOnePawnBPClass.Class != NULL)
    {
        P1Class = PlayerOnePawnBPClass;
    }
    
    if (PlayerTwoPawnBPClass.Class != NULL)
    {
        P2Class = PlayerTwoPawnBPClass;
    }*/

}

UClass* ABubblepopGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    auto firstPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    
    //int32 id = ((APlayerController*)InController)->GetLocalPlayer()->GetControllerId();
    
    
    
    if (firstPlayer == InController)
    {
        FString PlayerOneChoice = Cast<UBubblepopGameInstance>(GetGameInstance())->FirstGameClass;

        if (PlayerOneChoice == "Rifle")
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character1"));
            
            //return PlayerPawnBPClass.Class;
            
            //return ACharacter1::StaticClass();
            return Char1Class;
        }
        else if (PlayerOneChoice == "Shotgun")
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character2"));
            
            //return PlayerPawnBPClass.Class;
            //return ACharacter2::StaticClass();
            return Char2Class;
        }
        else
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character3"));
            
            //return PlayerPawnBPClass.Class;
            //return ACharacter3::StaticClass();
            return Char3Class;
        }

    }
    
    else
    {
        FString PlayerTwoChoice = Cast<UBubblepopGameInstance>(GetGameInstance())->SecondGameClass;
        if (PlayerTwoChoice == "Rifle")
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character1"));
            //return PlayerPawnBPClass.Class;
            //return ACharacter::StaticClass();
            return Char1Class;
        }
        else if (PlayerTwoChoice == "Shotgun")
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character2"));
            //return PlayerPawnBPClass.Class;
            //return ACharacter2::StaticClass();
            return Char2Class;
        }
        else
        {
            //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character3"));
            //return PlayerPawnBPClass.Class;
            //return ACharacter3::StaticClass();
            return Char3Class;
        }
    }
}


void ABubblepopGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    if (MyModeNum == 0)
    {
        return;
    }
    
    

    /*if (GetNumPlayers() == 2)
    {
        GetWorld()->DestroyActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 1));
    }
    
    if (GetNumPlayers() == 1)
    {
        GetWorld()->DestroyActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }*/
    
    /*UBubblepopGameInstance* gi = Cast<UBubblepopGameInstance>(GetGameInstance());
    FString PlayerOneChoice = Cast<UBubblepopGameInstance>(GetGameInstance())->FirstGameClass;
    if (PlayerOneChoice == "Rifle")
    {
        P1Class = "Weapon1";
    }
    else if (PlayerOneChoice == "Shotgun")
    {
        P1Class = "Weapon2";
    }
    else
    {
        P1Class = "Weapon3";
    }*/
    
    /*FString PlayerTwoChoice = Cast<UBubblepopGameInstance>(GetGameInstance())->SecondGameClass;
    if (PlayerTwoChoice == "Rifle")
    {
        P2Class = "Weapon1";
    }
    else if (PlayerTwoChoice == "Shotgun")
    {
        P2Class = "Weapon2";
    }
    else
    {
        P2Class = "Weapon3";
    }*/
    

    /*if (P1Class == "Weapon1")
    {
        DefaultPawnClass = AWeapon1::StaticClass();

    }
    else if (P1Class == "Weapon2")
    {
        DefaultPawnClass = AWeapon2::StaticClass();
    }
    else
    {
        DefaultPawnClass = AWeapon3::StaticClass();

    }*/
    if (GetNumPlayers() == 1)
    {
        UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
    }
    
    

    /*if (P2Class == "Weapon1")
    {
        DefaultPawnClass = AWeapon1::StaticClass();
        
    }
    else if (P2Class == "Weapon2")
    {
        DefaultPawnClass = AWeapon2::StaticClass();
    }
    else
    {
        DefaultPawnClass = AWeapon3::StaticClass();
        
    }
    if (GetNumPlayers() == 1)
    {
        UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
    }*/
    
    GameStarted = true;
    RemainingTime = 120.0f;
    /*// Need to respawn another player
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
        GameStarted = false;
        auto PlayerOne = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
        auto PlayerTwo = Cast<ABubblepopCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),1));

        PlayerOneScore = PlayerOne->GetPlayerScore();
        PlayerTwoScore = PlayerTwo->GetPlayerScore();
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
