// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "MeleeWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class VAMPIREGAMEOLD_API AMeleeWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	AMeleeWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeleeWeapon")
	UBoxComponent* DamageBox;

protected:
	virtual void BeginPlay() override;

public:
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapImpactEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float Damage;
	
	UFUNCTION(BlueprintCallable)
	void TurnOnCollision();

	UFUNCTION(BlueprintCallable)
	void TurnOffCollision();

	UFUNCTION()
	void ThrowSword(FVector direction);
};
