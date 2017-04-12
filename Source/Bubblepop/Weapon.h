// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BubblepopCharacter.h"
#include "Weapon.generated.h"

UCLASS()
class BUBBLEPOP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    AWeapon();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
    USkeletalMeshComponent* WeaponMesh;
    
    // Rate of fire of this weapon
    UPROPERTY(EditAnywhere)
    float FireRate;
    
    // Range of this weapon
    UPROPERTY(EditAnywhere)
    float WeaponRange;
    
    // Damage for this weapon
    UPROPERTY(EditAnywhere, Category = Damage)
    float WeaponDamage;
    
    // Hit effect of this weapon
    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* HitParticle;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Getter for holder of this gun
    ABubblepopCharacter* GetHolder() const { return MyOwner; }
    
    // Setter for holder of this gun
    void SetHolder(ABubblepopCharacter* Character) { MyOwner = Character; }
    
    // Used to determine if this weapon has hit a surface
    void WeaponTrace();
    
    // Called when weapon starts to fire
    void OnStartFire();
    
    // Called when want weapon to stop firing
    void OnStopFire();
    
private:
    // Owner of this weapon
    ABubblepopCharacter* MyOwner;
    
    // Timer used to keep track of fire rate of this weapon
    FTimerHandle WeaponTimer;
    
    
    
};

