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
    
    void Tick(float DeltaSeconds) override;
    
private:
    void BeginPlay() override;
    float RemainingTime;
};



