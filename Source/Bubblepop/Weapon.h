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
    
    void CheckWeaponStatus();
    bool isReloading;
    void StartReloading();
    void DoneReloading();
    
    // Clip size of this weapon
    UPROPERTY(EditAnywhere)
    float WeaponClip;
    
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
    
    // Weapon Status
    UPROPERTY(EditAnywhere)
    float WeaponCanFire;

    
    // Current ammo of this weapon
    UPROPERTY(EditAnywhere)
    float WeaponCurrentAmmo;
    
    // Rload time of this weapon
    UPROPERTY(EditAnywhere)
    float WeaponReloadTime;
    
    // Damage for this weapon
    UPROPERTY(EditAnywhere, Category = Damage)
    float WeaponDamage;
    
    // Hit effect of this weapon
    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* HitParticle;
    
    // Sound when Firing
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* FireLoopSound;
    
    
    // Firing audio component
    UPROPERTY(Transient)
    class UAudioComponent* FireAC;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Getter for holder of this gun
    ABubblepopCharacter* GetHolder() const { return MyOwner; }
    
    // Setter for holder of this gun
    void SetHolder(ABubblepopCharacter* Character) { MyOwner = Character; }
    
    // Used to determine if this weapon has hit a surface
    void WeaponTrace();
    
    // For playing sounds
    UAudioComponent* PlayWeaponSound(USoundCue* Sound);

    
    // Called when weapon starts to fire
    void OnStartFire();
    
    // Called when want weapon to stop firing
    void OnStopFire();

	/*
		Effect Functions
	*/
	void RestoreDefaultForAll();

	void MultiplyWeaponDamage(float factor);
	void RestoreDefaultWeaponDamage();
    
private:
    // Owner of this weapon
    ABubblepopCharacter* MyOwner;
    
    // Timer used to keep track of fire rate of this weapon
    FTimerHandle WeaponTimer;
    FTimerHandle ReloadTimer;
    
    float DefaultFireRate = 0.1f;
	float DefaultWeaponDamage = 10.0f;
	float DefaultWeaponRange = 10000.0f;
    float DefaultWeaponClip = 30.0f;
    float DefaultReloadTime = 3.0f;
    
};

