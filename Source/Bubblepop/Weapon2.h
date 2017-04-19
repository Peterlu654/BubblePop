// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Weapon2.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEPOP_API AWeapon2 : public AWeapon
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;
	
	
};
