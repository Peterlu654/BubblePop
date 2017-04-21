// Fill out your copyright notice in the Description page of Project Settings.

#include "Bubblepop.h"
#include "Weapon.h"
#include "Character1.h"


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

// Fire weapon if have one
void AWeapon::OnStartFire()
{
    //FireAC = PlayWeaponSound(FireLoopSound);
    //MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, WeaponMesh, TEXT("MuzzleFlashSocket"));
    
    GetWorldTimerManager().SetTimer(WeaponTimer, this, &AWeapon::WeaponTrace,
                                    FireRate, true);
}

// Stop firing weapon if have one
void AWeapon::OnStopFire()
{
    /*if (FireAC != nullptr)
     {
     FireAC->Stop();
     PlayWeaponSound(FireFinishSound);
     }
     if (MuzzlePSC != nullptr)
     {
     MuzzlePSC->DeactivateSystem();
     }*/
    
    GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void AWeapon::WeaponTrace()
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


