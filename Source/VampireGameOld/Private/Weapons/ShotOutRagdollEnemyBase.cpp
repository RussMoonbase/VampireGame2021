// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShotOutRagdollEnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

// Sets default values
AShotOutRagdollEnemyBase::AShotOutRagdollEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//SetRootComponent(SphereComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	//SkeletalMeshComp->SetupAttachment(GetRootComponent());

	SetRootComponent(SkeletalMeshComp);
}

// Called when the game starts or when spawned
void AShotOutRagdollEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (SkeletalMeshComp)
	{
		//SkeletalMeshComp->SetCollisionProfileName(TEXT("ShotRagdoll"));
      SkeletalMeshComp->SetAllBodiesBelowSimulatePhysics(FName("Hips"), true);
      SkeletalMeshComp->SetAllBodiesBelowPhysicsBlendWeight(FName("Hips"), 1);
	}
	
	bHitSucceeded = false;
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
      SkeletalMeshComp->AddForce(ShootVector * ShotSpeed * SkeletalMeshComp->GetMass());
   }
	//if (SphereComp)
	//{
	//	SphereComp->AddForce(ShootVector * ShotSpeed * SphereComp->GetMass());
	//}
}

void AShotOutRagdollEnemyBase::AddDamage(AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}

	if (!bHitSucceeded)
	{
		bHitSucceeded = true;
      UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, GetOwner(), UDamageType::StaticClass());
      TurnOffCollision();
	}
}

void AShotOutRagdollEnemyBase::TurnOffCollision()
{
	if (DamageBoxes.Num() > 0)
	{
		for (UBoxComponent* aBox : DamageBoxes)
		{
			D("DAMAGE BOX COLLISION TURNED OFF");
		}
	}
}
