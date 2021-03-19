// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AV2021PlayerCharacter;
class UWidgetComponent;
//class UUserWidget;
class UBoxComponent;
class UAnimMontage;

UCLASS()
class VAMPIREGAMEOLD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp;

	UFUNCTION()
	void ActivateLevitate();

	UFUNCTION()
	void SetEnemyLevitateNumber(int theNum);

	UFUNCTION()
	void FlingDownedEnemy(FVector ForwardVector);

	UFUNCTION()
	bool GetbCanBePickedUp();

	UFUNCTION()
	void SetbCanBePickedUp(bool booleanValue);

	UFUNCTION()
	bool GetbStartFloating();

	UFUNCTION()
	void SetTargetDotVisibility(bool booleanValue);

	bool bIsLevitating;
	bool bGravity;

	float gameTime;

	AV2021PlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* TargetWidgetComp;

   UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
   UAnimMontage* HitMontage;

	UFUNCTION(BlueprintCallable, Category = "Hit Box")
	void RightSideHit();

   UFUNCTION(BlueprintCallable, Category = "Hit Box")
   void FrontStomachHit();

   UFUNCTION(BlueprintCallable, Category = "Hit Box")
   void TopHeadHit();

private:
	void FloatEnemy(float DeltaTime);

	void Levitate(float DeltaTime);

	float OrginalZLocationBeforeLevitate;

	float AngleAxis;

	bool bCanBePickedUp;

	bool bStartFloating;

	bool bIsDead;

	int EnemyLevitateNumber;

	FVector AxisVector;

	FVector Dimensions;

};
