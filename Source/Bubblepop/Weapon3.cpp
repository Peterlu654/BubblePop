// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Weapon3.h"

void AWeapon3::BeginPlay()
{
    Super::BeginPlay();
    
    
    FireRate = 0.05f;
    WeaponRange = 10000.0f;
    WeaponDamage = 5.0f;
    //WeaponClip = 8.0f;
}


