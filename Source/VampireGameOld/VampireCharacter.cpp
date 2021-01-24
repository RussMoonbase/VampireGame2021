// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MeleeWeapon.h"

// Sets default values
AVampireCharacter::AVampireCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsMeleeAttacking = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

// Called when the game starts or when spawned
void AVampireCharacter::BeginPlay()
{
	Super::BeginPlay();

	MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(MeleeWeaponClass);
	MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	MeleeWeapon->SetOwner(this);

}

// Called every frame
void AVampireCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVampireCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AVampireCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AVampireCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AVampireCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AVampireCharacter::TurnRight);

	PlayerInputComponent->BindAction(TEXT("MeleeAttack"), IE_Pressed, this, &AVampireCharacter::MeleeAttackButtonDown);
	PlayerInputComponent->BindAction(TEXT("MeleeAttack"), IE_Released, this, &AVampireCharacter::MeleeAttackButtonUp);
}

void AVampireCharacter::MoveForward(float AxisValue)
{
   if (Controller != nullptr && AxisValue != 0.0f)
   {
		const FRotator Rotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector MovementDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

      AddMovementInput(MovementDirection, AxisValue);
   }
}

void AVampireCharacter::MoveRight(float AxisValue)
{
   if (Controller != nullptr && AxisValue != 0.0f)
   {
		const FRotator Rotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector MovementDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

      AddMovementInput(MovementDirection, AxisValue);
   }
}

void AVampireCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AVampireCharacter::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AVampireCharacter::MeleeAttackButtonDown()
{
	MeleeAttack();
}

void AVampireCharacter::MeleeAttackButtonUp()
{
	IsMeleeAttacking = false;
}

void AVampireCharacter::MeleeAttack()
{
	IsMeleeAttacking = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && MeleeMontage)
	{
		AnimInstance->Montage_Play(MeleeMontage, 1.25f);
		AnimInstance->Montage_JumpToSection(FName("Attack_1"), MeleeMontage);
	}

}

