// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "PlayerBubble.h"
#include "GameFramework/Character.h"
#include "BubblepopCharacter.generated.h"

UCLASS(config=Game)
class ABubblepopCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
    
   
public:
	ABubblepopCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
    
    // Fire weapon if have one
    void OnStartFire();
    
    // Stop firing weapon if have one
    void OnStopFire();

    float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    // Getter for this character's score
    int GetPlayerScore() { return CharacterScore; }

	void PopBubble();

	void AddScoreAfterPopping();
    
    void RespawnNoob();
    
    FVector SpawnPoints[11] =
    {
        FVector(-1550, 1150, 150),
        FVector(-1750, -1400, 150),
        FVector(-1150, -750, 550),
        FVector(0, -1350, 350),
        FVector(950, -950, 150),
        FVector(950, 1350, 150),
        FVector(-450, 1350, 350),
        FVector(-450, 350, 550),
        FVector(150, 350, 550),
        FVector(950, 50, 550),
        FVector(-1750, -250, 150)
    };
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Assets")
    USkeletalMesh* CharacterMesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Assets")
    USkeletalMesh* TombstoneMesh;
    
    UPROPERTY(VisibleAnywhere, Category = SkeletalMesh)
    class USkeletalMeshComponent* PlayerMesh;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
    
    UPROPERTY(EditAnywhere, Category = Weapon)
    TSubclassOf<class AWeapon> WeaponClass;
    
    void setJump(float value);
    void BeginPlay() override;

	
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UPROPERTY(EditAnywhere, Category = Bubble)
	TSubclassOf<class APlayerBubble> BubbleClass;
    
    // Health
    UPROPERTY(EditAnywhere)
    float CharacterHealth;
    
    // Player Score
    int CharacterScore = 0;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/*
		Effects
	*/
	void RestoreDefaultForAll();

	void IncreaseCharacterHealth(int health);
	void RestoreDefaultCharacterHealth();

	void IncreasePopScore(int score);
	void RestoreDefaultPopScore();

	void MultiplyWalkSpeed(float Factor);
	void RestoreDefaultWalkSpeed();

	void MultiplyDamageResistance();
	void RestoreDefaultDamageResistance();


private:
	int PlayerId;

    class AWeapon* MyWeapon;
	float DamageResistance;

	class APlayerBubble* MyBubble;
	bool InBubble;
	bool BubblePopped;
	int PopScore;

	void ClearBubbleAfterTimeOut();
	float BubbleTimeout = 5.0f;

	const int DefaultCharacterHealth = 100;
	const int DefaultPopScore = 10;
	const float DefaultWalkSpeed = 600.0f;
	const float DefaultDamageResistance = 1.0f;
};

