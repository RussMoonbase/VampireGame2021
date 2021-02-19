// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/V2021CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/WeaponBase.h"
#include "Weapons/MeleeWeaponBase.h"
#include "Animation/AnimInstance.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "VampireGameOld/Enemy.h"
#include "Weapons/FingerGun.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(x));}

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
	
   AnimMontageMeleeSectionNum = 1;
   bIsPickingUp = false;
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

   PlayerInputComponent->BindAction(TEXT("MeleeAttack"), IE_Pressed, this, &AV2021CharacterBase::MeleeAttackButtonDown);
   PlayerInputComponent->BindAction(TEXT("MeleeAttack"), IE_Released, this, &AV2021CharacterBase::MeleeAttackButtonUp);

   PlayerInputComponent->BindAction(TEXT("PickUpAttack"), IE_Pressed, this, &AV2021CharacterBase::PickUpAttackButtonDown);
   PlayerInputComponent->BindAction(TEXT("PickUpAttack"), IE_Released, this, &AV2021CharacterBase::PickUpAttackButtonUp);

   PlayerInputComponent->BindAction(TEXT("FlingAttack"), IE_Pressed, this, &AV2021CharacterBase::FlingAttackButtonDown);

   PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AV2021CharacterBase::StartShoot);
   PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AV2021CharacterBase::StopShoot);

}

void AV2021CharacterBase::MoveForward(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0.0f && !bIsMeleeAttacking && !bIsPickingUp)
	{
		const FRotator Rotation(0.0, Controller->GetControlRotation().Yaw, 0.0);
		const FVector MovementDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(MovementDirection, AxisValue);
	}
}

void AV2021CharacterBase::MoveRight(float AxisValue)
{
   if (Controller != nullptr && AxisValue != 0.0f && !bIsMeleeAttacking)
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

void AV2021CharacterBase::MeleeAttackButtonDown()
{
	MeleeAttack();
}

void AV2021CharacterBase::MeleeAttackButtonUp()
{
   //if (bAttackEnd = true)
   //{

   //}
   if (AnimMontageMeleeSectionNum == 1)
   {
      AnimMontageMeleeSectionNum++;
   }
   else if (AnimMontageMeleeSectionNum == 2)
   {
      AnimMontageMeleeSectionNum--;
   }
}

void AV2021CharacterBase::MeleeAttack()
{
   bIsMeleeAttacking = true;

   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && MeleeMontage)
   {

      if (AnimMontageMeleeSectionNum == 1)
      {
         AnimInstance->Montage_Play(MeleeMontage, 1.25f);
         AnimInstance->Montage_JumpToSection(FName("Attack_1"), MeleeMontage);

      }
      else if (AnimMontageMeleeSectionNum == 2)
      {
         AnimInstance->Montage_Play(MeleeMontage, 1.25f);
         AnimInstance->Montage_JumpToSection(FName("Attack_2"), MeleeMontage);
      }

      //FName CurrentSection = AnimInstance->Montage_GetCurrentSection(MeleeMontage);

      //if (CurrentSection.IsNone())
      //{
      //   AnimInstance->Montage_Play(MeleeMontage, 1.25f);
      //}
      //else if (CurrentSection.IsEqual("Attack_1") && bAcceptsAttack2Input)
      //{
      //   AnimInstance->Montage_JumpToSection(FName("Attack_2"), MeleeMontage);
      //}
      //else if (CurrentSection.IsEqual("Attack_2") && bAcceptsAttack3Input)
      //{
      //   AnimInstance->Montage_JumpToSection(FName("Attack_3"), MeleeMontage);
      //}

      //AnimInstance->Montage_Play(MeleeMontage, 1.25f);
      //AnimInstance->Montage_JumpToSection(FName("Attack_1"), MeleeMontage);
   }
}

void AV2021CharacterBase::PickUpAttackButtonDown()
{

   if (bIsPickingUp)
   {
      return;
   }

   bIsPickingUp = true;

   TArray<TEnumAsByte<EObjectTypeQuery>> OVerlappedActorsArray;
   OVerlappedActorsArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

   TArray<AActor*> ignoreThis;
   ignoreThis.Init(this, 1);

   float radius = 200.0f;

   TArray<AActor*> outActors;

   FVector sphereSpawnLocation = GetActorLocation();

   UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, radius, OVerlappedActorsArray, AActor::StaticClass(), ignoreThis, outActors);
   DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 12, FColor::Red, true, 1.0f);

   for (AActor* outActor : outActors)
   {
      D("Overlapped Actor");
      AEnemy* TempEnemy = Cast<AEnemy>(outActor);

      if (TempEnemy->GetbCanBePickedUp())
      {
         TempEnemy->SetbCanBePickedUp(false);
         TargetPickUpEnemies.Add(TempEnemy);
      }
      //TargetPickUpEnemies.Add(Cast<AEnemy>(outActor));
   }

   for (AEnemy* targetPickUpEnemy : TargetPickUpEnemies)
   {
      if (targetPickUpEnemy)
      {
         targetPickUpEnemy->ActivateLevitate();
      }
   }

   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && PickUpMontage)
   {
      AnimInstance->Montage_Play(PickUpMontage, 0.85f);
      AnimInstance->Montage_JumpToSection(FName("CastSpell"), PickUpMontage);
   }

}

void AV2021CharacterBase::PickUpAttackButtonUp()
{

}

void AV2021CharacterBase::FlingAttackButtonDown()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && PickUpMontage)
   {
      AnimInstance->Montage_Play(PickUpMontage, 0.85f);
      AnimInstance->Montage_JumpToSection(FName("Throw"), PickUpMontage);
   }

   FVector PlayerForwardVector = GetActorForwardVector();

   if (TargetPickUpEnemies.Num() > 0)
   {
      int i = TargetPickUpEnemies.Num() - 1;
      UE_LOG(LogTemp, Warning, TEXT("Index of TargetPickUp Enemies = %d"), i);

      if (TargetPickUpEnemies[i])
      {
         TargetPickUpEnemies[i]->FlingDownedEnemy(PlayerForwardVector);
         TargetPickUpEnemies.RemoveAt(i);
      }
   }
}

void AV2021CharacterBase::StartShoot()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && ShootMontage)
   {
      AnimInstance->Montage_Play(ShootMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("Shoot_1"), ShootMontage);
   }

   //if (EquippedFingerGun)
   //{
   //   EquippedFingerGun->StartShooting();
   //}


}

void AV2021CharacterBase::StopShoot()
{

}

AFingerGun* AV2021CharacterBase::GetEquippedFingerGun()
{
	return EquippedFingerGun;
}

AFingerGun* AV2021CharacterBase::EquipWeapon(TSubclassOf<AFingerGun> NewWeapon)
{
   if (EquippedFingerGun)
   {
      UnequipWeapon();
   }

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	EquippedFingerGun = GetWorld()->SpawnActor<AFingerGun>(NewWeapon, Params);

	if (EquippedFingerGun)
	{
		EquippedFingerGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponAttachSocket);
		return EquippedFingerGun;
	}
	return nullptr;
}

void AV2021CharacterBase::UnequipWeapon()
{
	if (EquippedFingerGun)
	{
		EquippedFingerGun->OnUnequipped();
		EquippedFingerGun->Destroy();
	}
}

AMeleeWeaponBase* AV2021CharacterBase::GetEquippedMeleeWeapon()
{
   return EquippedMeleeWeapon;
}

AMeleeWeaponBase* AV2021CharacterBase::EquipMeleeWeapon(TSubclassOf<AMeleeWeaponBase> NewWeapon)
{
   if (EquippedMeleeWeapon)
   {
      UnequipWeapon();
   }

   FActorSpawnParameters Params;
   Params.Owner = this;
   Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   EquippedMeleeWeapon = GetWorld()->SpawnActor<AMeleeWeaponBase>(NewWeapon, Params);

   if (EquippedMeleeWeapon)
   {
      EquippedMeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponAttachSocket);
      return EquippedMeleeWeapon;
   }
   return nullptr;
}

void AV2021CharacterBase::UnequipMeleeWeapon()
{
   if (EquippedMeleeWeapon)
   {
      EquippedMeleeWeapon->OnUnequipped();
      EquippedMeleeWeapon->Destroy();
   }
}

void AV2021CharacterBase::SetAcceptsAttack2Input(bool booleanValue)
{
   bAcceptsAttack2Input = booleanValue;
}

void AV2021CharacterBase::SetAcceptsAttack3Input(bool booleanValue)
{
   bAcceptsAttack3Input = booleanValue;
}

void AV2021CharacterBase::SetAttackEnd(bool booleanValue)
{
   bAttackEnd = booleanValue;

   bIsMeleeAttacking = false; // FIX THIS so it uses the booleanValue parameter
}

void AV2021CharacterBase::SetIsPickingUp(bool booleanValue)
{
   bIsPickingUp = booleanValue;
}

