// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "BubblepopGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API UBubblepopGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString FirstGameClass = "Rifle";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SecondGameClass = "Rifle";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GameMap = "Jungle";
    
    UBubblepopGameInstance();
    
    
	
	
};
