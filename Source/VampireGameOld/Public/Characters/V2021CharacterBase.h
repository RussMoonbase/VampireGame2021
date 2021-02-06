// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "V2021CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AWeaponBase;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vampire2021")
	float BaseTurnSpeed = 10.0;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	AWeaponBase* GetEquippedWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	AWeaponBase* EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void UnequipWeapon();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	FName WeaponAttachSocket;

private:
	AWeaponBase* EquippedWeapon;

};
