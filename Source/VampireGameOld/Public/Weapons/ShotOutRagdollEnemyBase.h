// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShotOutRagdollEnemyBase.generated.h"

class USkeletalMeshComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	USkeletalMeshComponent* SkeletalMeshComp;

	UFUNCTION()
	void FlingRadgoll(FVector ShootVector);

};
