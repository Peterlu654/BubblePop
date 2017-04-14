// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BubblepopGameMode.generated.h"

UCLASS(minimalapi)
class ABubblepopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABubblepopGameMode();
    
    float GetRemainingTime() const { return RemainingTime; }
    
    void Tick(float DeltaTime) override;
    
    static bool HasGameStarted();
    
private:
    void BeginPlay() override;
    void BeginDestroy() override;
    //void OnDestroy() override;
    float RemainingTime;
    int MyModeNum;
};



