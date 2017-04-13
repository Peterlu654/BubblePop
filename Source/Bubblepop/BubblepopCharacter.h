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
    float CharacterHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float CollisionRange = 2.0f;
    
    // Player Score
    int CharacterScore = 0;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


private:
	int PlayerId;

    class AWeapon* MyWeapon;
	
	class APlayerBubble* MyBubble;
	bool InBubble;
	bool BubblePopped;
};

