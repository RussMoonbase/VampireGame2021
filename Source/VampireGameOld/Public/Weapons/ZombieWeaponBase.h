// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieWeaponBase.generated.h"



UCLASS()
class VAMPIREGAMEOLD_API AZombieWeaponBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AddDamage(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void RagdollDeath();

	UPROPERTY(EditAnywhere)
	float DamageAmount = 300.0f;

	UPROPERTY()
	UCapsuleComponent* CapsuleComp;

};
