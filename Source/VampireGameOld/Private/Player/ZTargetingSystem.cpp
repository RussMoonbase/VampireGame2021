// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZTargetingSystem.h"
#include "Characters/V2021PlayerCharacter.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "VampireGameOld/Enemy.h"
#include "Math/Vector.h"
#include "Math/NumericLimits.h"
#include "Player/HealthComponent.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

// Sets default values for this component's properties
UZTargetingSystem::UZTargetingSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZTargetingSystem::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		PlayerCharacter = Cast<AV2021PlayerCharacter>(GetOwner());
	}


   if (PlayerCharacter)
   {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Player is active in ZTargeting"));
   }
	
}


// Called every frame
void UZTargetingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZTargetingSystem::LockOnTarget()
{
   if (lockedTargetEnemy)
   {
      lockedTargetEnemy->SetTargetDotVisibility(false);
   }

   TArray<TEnumAsByte<EObjectTypeQuery>> OverlappedActorsArray;
   OverlappedActorsArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

   TArray<AActor*> ignoreThis;
   ignoreThis.Init(PlayerCharacter, 1);

   TArray<AActor*> outActors;

   FVector sphereSpawnLocation;
   if (PlayerCharacter)
   {
      sphereSpawnLocation = PlayerCharacter->GetActorLocation();
   }
   else
   {
      sphereSpawnLocation = GetOwner()->GetActorLocation();
   }

   UClass* classToTarget = AEnemy::StaticClass();
   UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, targetSphereRadius, OverlappedActorsArray, classToTarget, ignoreThis, outActors);
   DrawDebugSphere(GetWorld(), sphereSpawnLocation, targetSphereRadius, 12, FColor::Yellow, true, -1.0f);

   closestTargetDistance = TNumericLimits<float>::Max();
   for (AActor* outActor : outActors)
   {
      float targetDistance = (outActor->GetActorLocation() - PlayerCharacter->GetActorLocation()).SizeSquared();

      if (outActor->FindComponentByClass<UHealthComponent>())
      {
         bool isDead = outActor->FindComponentByClass<UHealthComponent>()->GetIsDead();
         if (targetDistance < closestTargetDistance && !isDead)
         {
            closestTargetDistance = targetDistance;
            lockedTargetActor = outActor;
         }
      }
      //if (targetDistance < closestTargetDistance)
      //{
      //   closestTargetDistance = targetDistance;
      //   //smallestDistanceEnemy = outActor->GetName();
      //   lockedTargetActor = outActor;
      //}
   }

   lockedTargetEnemy = Cast<AEnemy>(lockedTargetActor);
   GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Locked On Enemy = %s"), *lockedTargetEnemy->GetName()));

   if (lockedTargetEnemy)
   {
      lockedTargetEnemy->SetTargetDotVisibility(true);
   }

   if (PlayerCharacter)
   {
      PlayerCharacter->TurnOnLockedOnCam();

      if (lockedTargetEnemy)
      {
         PlayerCharacter->SetLockedOnEnemy(lockedTargetEnemy);
      }
   }

   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shortest Distance Enemy Name = %s"), *smallestDistanceEnemy));
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shortest Distance = %f"), closestTargetDistance));
}

void UZTargetingSystem::TurnOffLockOnTarget()
{
   if (lockedTargetEnemy)
   {
      lockedTargetEnemy->SetTargetDotVisibility(false);
   }
}

