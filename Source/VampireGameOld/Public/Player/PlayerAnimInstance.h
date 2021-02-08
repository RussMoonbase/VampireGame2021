// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class AV2021CharacterBase;

UCLASS()
class VAMPIREGAMEOLD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
   APawn* ThePawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerCharacter")
	AV2021CharacterBase* ThePlayerCharacter;

};
