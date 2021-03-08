// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class AEnemy;
class ABombBase;

UCLASS()
class VAMPIREGAMEOLD_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	UProjectileMovementComponent* ProjecticleMoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	USphereComponent* DamageSphere;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bomb")
   TSubclassOf<ABombBase> MicroBomb;

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
   float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	float EnemyProximityDistance;

   UFUNCTION()
   void OnOverlapImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void SpawnMicroBombs();

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
	void OnImpact(const FHitResult& Hit);

   UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
   void OnTargetReached(FVector theLocation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AEnemy* LockedOnEnemy;

	float targetDistance;
	
	bool bTargetReached;

};
