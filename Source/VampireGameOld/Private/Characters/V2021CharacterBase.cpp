// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/V2021CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AV2021CharacterBase::AV2021CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm
	TheSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TheSpringArm->SetupAttachment(GetRootComponent());

	// Create Camera
	TheCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TheCameraComp->SetupAttachment(TheSpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0, 540.0, 0.0);
}

// Called when the game starts or when spawned
void AV2021CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AV2021CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AV2021CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

   PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AV2021CharacterBase::MoveForward);
   PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AV2021CharacterBase::MoveRight);
   PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AV2021CharacterBase::LookUp);
   PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AV2021CharacterBase::TurnRight);

}

void AV2021CharacterBase::MoveForward(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation(0.0, Controller->GetControlRotation().Yaw, 0.0);
		const FVector MovementDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(MovementDirection, AxisValue);
	}
}

void AV2021CharacterBase::MoveRight(float AxisValue)
{
   if (Controller != nullptr && AxisValue != 0.0f)
   {
      const FRotator Rotation(0.0, Controller->GetControlRotation().Yaw, 0.0);
      const FVector MovementDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

      AddMovementInput(MovementDirection, AxisValue);
   }
}

void AV2021CharacterBase::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * BaseTurnSpeed * GetWorld()->GetDeltaSeconds());
}

void AV2021CharacterBase::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * BaseTurnSpeed * GetWorld()->GetDeltaSeconds());
}

