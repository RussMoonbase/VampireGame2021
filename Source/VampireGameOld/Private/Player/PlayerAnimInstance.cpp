// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnimInstance.h"
#include "Characters/V2021CharacterBase.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
   if (ThePawn == nullptr)
   {
      ThePawn = TryGetPawnOwner();

      if (ThePawn)
      {
         ThePlayerCharacter = Cast<AV2021CharacterBase>(ThePawn);
      }
   }
}
