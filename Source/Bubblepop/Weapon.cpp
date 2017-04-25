// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Weapon.h"
#include "Character1.h"
#include <iostream>

// Sets default values
AWeapon::AWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    
    FireRate = DefaultFireRate;
    WeaponRange = DefaultWeaponRange;
    WeaponDamage = DefaultWeaponDamage;
    WeaponClip = DefaultWeaponClip;
    WeaponReloadTime = DefaultReloadTime;
    WeaponCurrentAmmo = DefaultWeaponClip;
    WeaponCanFire = true;
    isReloading = false;
    
    FireAC = nullptr;
    
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    if (Sound)
    {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    return AC;
}

// Fire weapon if have one
void AWeapon::OnStartFire()
{
    if (WeaponCanFire)
    {
        FireAC = PlayWeaponSound(FireLoopSound);
        GetWorldTimerManager().SetTimer(WeaponTimer, this, &AWeapon::WeaponTrace, FireRate, true);
    }
    else
    {
        if (!isReloading)
        {
            StartReloading();
        }
    }
}


// Stop firing weapon if have one
void AWeapon::OnStopFire()
{
    if (FireAC != nullptr)
     {
         FireAC->Stop();
     }
    
    GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void AWeapon::WeaponTrace()
{
    if (WeaponCanFire)
    {
        static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
        static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
        // Start from the muzzle's position
        FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
        
        //FRotator rotate(30.0f, 0.0f, 0.0f);
        // Get forward vector of Camera
        //FVector CameraDirection = MyOwner->GetFollowCamera()->GetForwardVector();
        //FVector Forward = rotate.RotateVector(CameraDirection);
        FVector Forward = MyOwner->GetFollowCamera()->GetForwardVector();
        // Calculate end position
        FVector EndPos = StartPos + Forward * WeaponRange;
        // Perform trace to retrieve hit info
        FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
        TraceParams.bTraceAsyncScene = true;
        TraceParams.bReturnPhysicalMaterial = true;
        // This fires the ray and checks against all objects w/ collision
        FHitResult Hit(ForceInit);
        GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
                                                FCollisionObjectQueryParams::AllObjects, TraceParams);
        // Did this hit anything?
        if (Hit.bBlockingHit)
        {
            // TODO: Actually do something
            UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, Hit.ImpactPoint);
            
            ACharacter1* target = Cast<ACharacter1>(Hit.GetActor());
            if (target){
                target->TakeDamage(WeaponDamage, FDamageEvent(), GetInstigatorController(), this);
            }
        }
        
        WeaponCurrentAmmo--;
        CheckWeaponStatus();
    }
    else
    {
        StartReloading();
    }
}

void AWeapon::StartReloading()
{
    if (!isReloading)
    {
        GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeapon::DoneReloading, WeaponReloadTime, false);
    }
    isReloading = true;
}

void AWeapon::DoneReloading()
{
    isReloading = false;
    WeaponCanFire = true;
    WeaponCurrentAmmo = WeaponClip;
}

void AWeapon::CheckWeaponStatus()
{
    if (WeaponCurrentAmmo <= 0)
    {
        WeaponCanFire = false;
    }
    else
    {
        WeaponCanFire = true;
    }
}

void AWeapon::RestoreDefaultForAll() {
	RestoreDefaultWeaponDamage();
}

void AWeapon::MultiplyWeaponDamage(float factor) {
	WeaponDamage = DefaultWeaponDamage * factor;
}
void AWeapon::RestoreDefaultWeaponDamage() {
	WeaponDamage = DefaultWeaponDamage;
}
