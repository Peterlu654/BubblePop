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
    
private:
    void BeginPlay() override;
};



