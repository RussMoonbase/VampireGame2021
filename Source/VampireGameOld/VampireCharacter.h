// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VampireCharacter.generated.h"


class AMeleeWeapon;

UCLASS()
class VAMPIREGAMEOLD_API AVampireCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVampireCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* MeleeMontage;

private:
	// move forward/backward input
	void MoveForward(float AxisValue);

	// move left/right input
	void MoveRight(float AxisValue);

	// look up/down input
	void LookUp(float AxisValue);

	// look right/left input
	void TurnRight(float AxisValue);

	void MeleeAttackButtonDown();
	void MeleeAttackButtonUp();
	void MeleeAttack();

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.0f;

	bool IsMeleeAttacking;

	UPROPERTY(EditAnywhere)
	float  CameraPitchMax = 90.0f;
	
   UPROPERTY(EditAnywhere)
   float  CameraPitchMin = -90.0f;

   UPROPERTY(EditDefaultsOnly)
      TSubclassOf<AMeleeWeapon> MeleeWeaponClass;

   UPROPERTY()
      AMeleeWeapon* MeleeWeapon;
};
