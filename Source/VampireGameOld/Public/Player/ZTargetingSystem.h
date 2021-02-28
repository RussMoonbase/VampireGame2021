// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZTargetingSystem.generated.h"

class AV2021PlayerCharacter;
class AEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREGAMEOLD_API UZTargetingSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZTargetingSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Character")
	AV2021PlayerCharacter* PlayerCharacter;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting System")
   float targetSphereRadius = 1000.0f;

	UFUNCTION()
	void LockOnTarget();

private:
	float closestTargetDistance;

	AActor* lockedTargetActor;
	AEnemy* lockedTargetEnemy;
		
};
