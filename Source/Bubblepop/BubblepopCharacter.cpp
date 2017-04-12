// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Bubblepop.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "BubblepopCharacter.h"
#include "Weapon.h"


//////////////////////////////////////////////////////////////////////////
// ABubblepopCharacter

ABubblepopCharacter::ABubblepopCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
    
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    
    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    
    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
    
    MyWeapon = nullptr;
    MyBubble = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABubblepopCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    
    int32 id = ((APlayerController*)GetController())->GetLocalPlayer()->GetControllerId();
    if (id == 0)
    {
        PlayerInputComponent->BindAction("Jump1", IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction("Jump1", IE_Released, this, &ACharacter::StopJumping);
        
        PlayerInputComponent->BindAxis("MoveForward1", this, &ABubblepopCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight1", this, &ABubblepopCharacter::MoveRight);
        
        // We have 2 versions of the rotation bindings to handle different kinds of devices differently
        // "turn" handles devices that provide an absolute delta, such as a mouse.
        // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
        PlayerInputComponent->BindAxis("Turn1", this, &APawn::AddControllerYawInput);
        //PlayerInputComponent->BindAxis("TurnRate", this, &ABubblepopCharacter::TurnAtRate);
        PlayerInputComponent->BindAxis("LookUp1", this, &APawn::AddControllerPitchInput);
        //PlayerInputComponent->BindAxis("LookUpRate", this, &ABubblepopCharacter::LookUpAtRate);
        
        // handle touch devices
        PlayerInputComponent->BindTouch(IE_Pressed, this, &ABubblepopCharacter::TouchStarted);
        PlayerInputComponent->BindTouch(IE_Released, this, &ABubblepopCharacter::TouchStopped);
        
        PlayerInputComponent->BindAction("Fire1", IE_Pressed, this, &ABubblepopCharacter::OnStartFire);
        PlayerInputComponent->BindAction("Fire1", IE_Released, this, &ABubblepopCharacter::OnStopFire);
    }
    else if(id == 1)
    {
        PlayerInputComponent->BindAction("Jump2", IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction("Jump2", IE_Released, this, &ACharacter::StopJumping);
        
        PlayerInputComponent->BindAxis("MoveForward2", this, &ABubblepopCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight2", this, &ABubblepopCharacter::MoveRight);
        
        // We have 2 versions of the rotation bindings to handle different kinds of devices differently
        // "turn" handles devices that provide an absolute delta, such as a mouse.
        // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
        PlayerInputComponent->BindAxis("Turn2", this, &APawn::AddControllerYawInput);
        //PlayerInputComponent->BindAxis("TurnRate", this, &ABubblepopCharacter::TurnAtRate);
        PlayerInputComponent->BindAxis("LookUp2", this, &APawn::AddControllerPitchInput);
        //PlayerInputComponent->BindAxis("LookUpRate", this, &ABubblepopCharacter::LookUpAtRate);
        
        // handle touch devices
        PlayerInputComponent->BindTouch(IE_Pressed, this, &ABubblepopCharacter::TouchStarted);
        PlayerInputComponent->BindTouch(IE_Released, this, &ABubblepopCharacter::TouchStopped);
        
        PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &ABubblepopCharacter::OnStartFire);
        PlayerInputComponent->BindAction("Fire2", IE_Released, this, &ABubblepopCharacter::OnStopFire);
    }
}


void ABubblepopCharacter::OnResetVR()
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABubblepopCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void ABubblepopCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void ABubblepopCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABubblepopCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABubblepopCharacter::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ABubblepopCharacter::MoveRight(float Value)
{
    if ( (Controller != NULL) && (Value != 0.0f) )
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

// Fire weapon if have one
void ABubblepopCharacter::OnStartFire()
{
    if (MyWeapon != nullptr)
    {
        MyWeapon->OnStartFire();
    }
}

// Stop firing weapon if have one
void ABubblepopCharacter::OnStopFire()
{
    if (MyWeapon != nullptr)
    {
        MyWeapon->OnStopFire();
    }
}

void ABubblepopCharacter::BeginPlay() {
    // Call base class BeginPlay
    Super::BeginPlay();
    
    if (BubbleClass) {
        UWorld* World = GetWorld();
        if (World != nullptr) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            // Need to set rotation like this because otherwise gun points down
            FRotator Rotation(0.0f, 0.0f, 0.0f);
            
            MyBubble = World->SpawnActor<APlayerBubble>(BubbleClass, FVector::ZeroVector, Rotation, SpawnParams);
            if (MyBubble != nullptr) {
                MyBubble->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
            }
        }
    }
    
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
            MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector(-20.0f, 10.0f, 100.0f),
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
}
