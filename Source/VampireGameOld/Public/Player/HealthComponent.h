// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeathValueChange, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREGAMEOLD_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	float CurrentHealth;

	UFUNCTION()
	void OnOwnerTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float StartHealth = 0.0f;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
	bool GetIsDead();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHeathValueChange OnHealthValueChange;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDied OnDied;
		
};
