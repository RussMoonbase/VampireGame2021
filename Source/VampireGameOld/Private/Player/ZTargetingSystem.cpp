// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZTargetingSystem.h"
#include "Characters/V2021PlayerCharacter.h"

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
	// ...
	
}


// Called every frame
void UZTargetingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZTargetingSystem::LockOnTarget()
{

}

