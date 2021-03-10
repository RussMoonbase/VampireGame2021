// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class VAMPIREGAMEOLD_API ABombBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombBase();

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
   USphereComponent* DamageSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	UStaticMeshComponent* MeshComp;

	UFUNCTION(BlueprintImplementableEvent, Category = "Bomb")
	void OnHit(const FHitResult& Hit);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	//UProjectileMovementComponent* ProjectileMoveComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void AddExplosiveForce();

private:
	bool bBombHasHit;

};
