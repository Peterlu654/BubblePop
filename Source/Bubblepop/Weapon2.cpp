// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Weapon2.h"

void AWeapon2::BeginPlay()
{
    Super::BeginPlay();
    
    //Revolver Stats
    FireRate = 0.2f;
    WeaponRange = 10000.0f;
    WeaponDamage = 20.0f;
    WeaponClip = 8.0f;
    WeaponReloadTime = 4.0f;
    WeaponCurrentAmmo = WeaponClip;
    
}
