// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShotOutRagdollEnemyBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AShotOutRagdollEnemyBase::AShotOutRagdollEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SetRootComponent(SkeletalMeshComp);
}

// Called when the game starts or when spawned
void AShotOutRagdollEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (SkeletalMeshComp)
	{
		SkeletalMeshComp->SetCollisionProfileName(TEXT("ShotRagdoll"));
      SkeletalMeshComp->SetAllBodiesBelowSimulatePhysics(FName("Hips"), true);
      SkeletalMeshComp->SetAllBodiesBelowPhysicsBlendWeight(FName("Hips"), 1);
	}
	
}

// Called every frame
void AShotOutRagdollEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShotOutRagdollEnemyBase::FlingRadgoll(FVector ShootVector)
{
	if (SkeletalMeshComp)
	{
		SkeletalMeshComp->AddForce(ShootVector * 100000 * SkeletalMeshComp->GetMass());
	}
}

