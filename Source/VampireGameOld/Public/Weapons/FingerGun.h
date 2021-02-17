// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FingerGun.generated.h"


class ABulletBase;

UCLASS()
class VAMPIREGAMEOLD_API AFingerGun : public AActor
{
	GENERATED_BODY()

private:
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Finger Weapon", meta = (AllowPrivateAccess = "true"))
   class USceneComponent* RootComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Finger Weapon", meta = (AllowPrivateAccess = "true"))
   class UArrowComponent* GunMuzzleArrow;

public:	
	// Sets default values for this actor's properties
	AFingerGun();

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Finger Weapon")
   TSubclassOf<ABulletBase> Bullet;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Finger Weapon")
   float RefireRate = 0.1f;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Finger Weapon")
   int CurrentAmmo = 3;

   UFUNCTION(BlueprintNativeEvent, Category = "Finger Weapon")
   void StartShooting();

   UFUNCTION(BlueprintNativeEvent, Category = "Finger Weapon")
   void StopShooting();

   UFUNCTION(BlueprintImplementableEvent, Category = "Finger Weapon")
   void OnEquipped();

   UFUNCTION(BlueprintImplementableEvent, Category = "Finger Weapon")
   void OnUnequipped();

   UFUNCTION(BlueprintCallable)
   void StartFiring();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

   UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
   void FireGhostBullet();


};
