// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Character3.h"


void ACharacter3::BeginPlay() {
    Super::BeginPlay();
    
    if (CharacterMesh){
        PlayerMesh->SetSkeletalMesh(CharacterMesh);
    }
    /*
     // Spawn the weapon, if one was specified
     if (WeaponClass)
     {
     UWorld* World = GetWorld();
     if (World)
     {
     FActorSpawnParameters SpawnParams;
     SpawnParams.Owner = this;
     SpawnParams.Instigator = Instigator;
     // Need to set rotation like this because otherwise gun points down
     FRotator Rotation(0.0f, 0.0f, 0.0f);
     // Spawn the Weapon
     MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector(0.0f, 1.0f, 0.0f),
     Rotation, SpawnParams);
     if (MyWeapon)
     {
     // This is attached to "WeaponPoint" which is defined in the skeleton
     MyWeapon->AttachToComponent(GetMesh(),
     FAttachmentTransformRules::KeepRelativeTransform,
     TEXT("WeaponPoint"));
     
     MyWeapon->SetHolder(this);
     
     }
     }
     }
     */
}
