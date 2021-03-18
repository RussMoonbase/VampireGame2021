// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AV2021PlayerCharacter;
class UWidgetComponent;
//class UUserWidget;

class UBoxComponent;

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

   //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
   //UBoxComponent* HeadHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* BodyLeftHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* BodyRightHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* LeftUpperArmHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* LeftLowerArmHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* RightUpperArmHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* RightLowerArmHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* LeftUpperLegHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* LeftLowerLegHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* RightUpperLegHitBox;

 //  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitBox")
 //  UBoxComponent* RightLowerLegHitBox;

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
