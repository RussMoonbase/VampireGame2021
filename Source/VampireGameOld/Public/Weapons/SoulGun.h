// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulGun.generated.h"

class AShotOutRagdollEnemyBase;
class USkeletalMeshComponent;

UCLASS()
class VAMPIREGAMEOLD_API ASoulGun : public AActor
{
	GENERATED_BODY()

private:
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Soul Gun", meta = (AllowPrivateAccess = "true"))
   class USceneComponent* RootComp;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Soul Gun", meta = (AllowPrivateAccess = "true"))
   class UArrowComponent* GunMuzzleArrow;
	
public:	
	// Sets default values for this actor's properties
	ASoulGun();

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Soul Gun")
   TSubclassOf<AShotOutRagdollEnemyBase> SpawnRagdoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul Gun")
	float shootSpeed;

	UFUNCTION()
	void FireSpawnedRagdollBullet(FVector targetVector, FTransform socketLocation);

	UFUNCTION()
	void TurnOnRagdollShield(USkeletalMeshComponent* SkeletalMeshComp, FName SocketName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
