// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAnimInstance.h"
#include "VampireGameOld/Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
   if (ThePawn == nullptr)
   {
      ThePawn = TryGetPawnOwner();

      if (ThePawn)
      {
         TheEnemy = Cast<AEnemy>(ThePawn);
      }
   }
}
