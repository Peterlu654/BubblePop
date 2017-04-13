// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BubblepopCharacter.h"
#include "Character1.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API ACharacter1 : public ABubblepopCharacter
{
	GENERATED_BODY()

private:
    class AWeapon* MyWeapon;
    void BeginPlay() override;
    class APlayerBubble* MyBubble;
};
