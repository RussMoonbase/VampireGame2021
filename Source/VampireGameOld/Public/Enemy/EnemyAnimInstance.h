// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AEnemy;

UCLASS()
class VAMPIREGAMEOLD_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
   virtual void NativeInitializeAnimation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyCharacter")
	APawn* ThePawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerCharacter")
	AEnemy* TheEnemy;
	
};
