// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Weapon1.h"

void AWeapon1::BeginPlay()
{
    Super::BeginPlay();
    
    //Submachine Gun Stats
    FireRate = 0.1f;
    WeaponRange = 10000.0f;
    WeaponDamage = 7.0f;
    WeaponClip = 45.0f;
    WeaponCurrentAmmo = WeaponClip;
    
}


