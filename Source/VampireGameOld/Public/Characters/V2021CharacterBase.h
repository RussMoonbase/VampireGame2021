// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "V2021CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AWeaponBase;
class AMeleeWeaponBase;
class AFingerGun;
class UAnimMontage;
class AEnemy;
class UStaticMeshComponent;
class UZTargetingSystem;
class ASoulGun;

UCLASS()
class VAMPIREGAMEOLD_API AV2021CharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TheCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* TheSpringArm;

public:
	// Sets default values for this character's properties
	AV2021CharacterBase();

	UCameraComponent* GetCameraComponent() { return TheCameraComp; }

	USpringArmComponent* GetSpringArm() { return TheSpringArm; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void TurnRight(float AxisValue);
	void LookUp(float AxisValue);
   void MeleeAttackButtonDown();
   void MeleeAttackButtonUp();
	void MeleeAttack();
	void PickUpAttackButtonDown();
	void PickUpAttackButtonUp();
	void FlingAttackButtonDown();
	void ThrowAttackButtonDown();
	void StartShoot();
	void StopShoot();
	void ActivateTargetingSystem();

   UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
   UAnimMontage* MeleeMontage;

   UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
   UAnimMontage* PickUpMontage;

   UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
   UAnimMontage* ShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vampire2021")
	float BaseTurnSpeed = 10.0;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	AFingerGun* GetEquippedFingerGun();

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   AFingerGun* EquipWeapon(TSubclassOf<AFingerGun> NewWeapon);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void UnequipWeapon();

	UFUNCTION(BlueprintPure, Category = "Weapons")
	AMeleeWeaponBase* GetEquippedMeleeWeapon();

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   AMeleeWeaponBase* EquipMeleeWeapon(TSubclassOf<AMeleeWeaponBase> NewWeapon);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void UnequipMeleeWeapon();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	FName WeaponAttachSocket;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetAcceptsAttack2Input(bool booleanValue);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void SetAcceptsAttack3Input(bool booleanValue);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void SetAttackEnd(bool booleanValue);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void SetIsPickingUp(bool booleanValue);

   UFUNCTION(BlueprintCallable, Category = "Powers")
   void EquipSoulSpheres();

	UFUNCTION()
	void TurnOnLockedOnCam();

	UFUNCTION()
	void SetLockedOnEnemy(AEnemy* theEnemy);

	UFUNCTION()
	void EquipLevitatingEnemy(AEnemy* theEnemy);

	UFUNCTION()
	void UnequipLevitatingEnemy(AEnemy* theEnemy);

	UFUNCTION()
	void TurnOffLockedOnCamera();

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Powers")
   FName SoulAttachSocket1;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Powers")
   FName SoulAttachSocket2;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Powers")
   FName SoulAttachSocket3;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Powers")
   FName SoulMuzzleSocket;

	// soul sphere meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powers")
	UStaticMeshComponent* SoulSphereMeshComp1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powers")
	UStaticMeshComponent* SoulSphereMeshComp2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powers")
	UStaticMeshComponent* SoulSphereMeshComp3;

	// to turn on mesh after player gets a soul
	UFUNCTION()
	void ActivateSoulSphere(int EnemyNumber);

	UFUNCTION()
	void DeactivateSoulSphere(int EnemyNumber);

	// targeting system for melee and projectile attacks
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Powers")
	UZTargetingSystem* TargetingSystemComp;

	UFUNCTION()
	AEnemy* GetLockedOnEnemy();

   UFUNCTION(BlueprintPure, Category = "Weapons")
   ASoulGun* GetEquippedSoulGun();

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   ASoulGun* EquipSoulGun(TSubclassOf<ASoulGun> NewSoulGun);

   UFUNCTION(BlueprintCallable, Category = "Weapons")
   void UnequipSoulGun();

private:
	AFingerGun* EquippedFingerGun;

	AMeleeWeaponBase* EquippedMeleeWeapon;

	ASoulGun* EquippedSoulGun;

	bool bAcceptsAttack3Input;

	bool bAcceptsAttack2Input;

	bool bAttackEnd;

	bool bIsMeleeAttacking;

	bool bIsPickingUp;

	bool bIsZTargetLockedOn;

	int AnimMontageMeleeSectionNum;

	AEnemy* TargetLevitatingEnemy;

	AEnemy* LockedOnEnemy;

	TArray<AEnemy*> TargetPickUpEnemies;

	void CameraLockOn();

	int EnemyCount;
};
