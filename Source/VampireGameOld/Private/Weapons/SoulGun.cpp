// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SoulGun.h"
#include "Components/ArrowComponent.h"
#include "Weapons/ShotOutRagdollEnemyBase.h"

// Sets default values
ASoulGun::ASoulGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
   SetRootComponent(RootComp);

   GunMuzzleArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("GunMuzzle"));
   GunMuzzleArrow->SetupAttachment(RootComp);
   GunMuzzleArrow->ArrowSize = 0.3f;
   GunMuzzleArrow->ArrowColor = FColor::Yellow;

}

// Called when the game starts or when spawned
void ASoulGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoulGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoulGun::FireSpawnedRagdollBullet(FVector targetVector)
{
	const FTransform SpawnTransform = GunMuzzleArrow->GetComponentTransform();

   FActorSpawnParameters Params;
   Params.Owner = GetOwner();
   Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AShotOutRagdollEnemyBase* RagdollBullet = GetWorld()->SpawnActor<AShotOutRagdollEnemyBase>(SpawnRagdoll, SpawnTransform, Params);

	if (RagdollBullet)
	{
		RagdollBullet->FlingRadgoll(targetVector);
	}
}


