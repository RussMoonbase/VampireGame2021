// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShotOutRagdollEnemyBase.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class USphereComponent;

UCLASS()
class VAMPIREGAMEOLD_API AShotOutRagdollEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShotOutRagdollEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ragdoll")
	USkeletalMeshComponent* SkeletalMeshComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ragdoll")
	//USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ragdoll")
	TArray<UBoxComponent*> DamageBoxes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ragdoll")
	float Damage = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ragdoll")
	float ShotSpeed = 100000;

	UFUNCTION()
	void FlingRadgoll(FVector ShootVector);

	UFUNCTION()
	void RagdollShield();

	UFUNCTION(BlueprintCallable)
	void AddDamage(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void TurnOffCollision();

private:
	bool bHitSucceeded;

};
