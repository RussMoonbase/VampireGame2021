// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BombBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABombBase::ABombBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
   SetRootComponent(DamageSphere);


   //DamageSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
   MeshComp->SetupAttachment(DamageSphere);

   if (GetOwner())
   {
      MeshComp->IgnoreActorWhenMoving(GetOwner(), true);
   }

	//ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
 //  ProjectileMoveComp->InitialSpeed = 200.0f;

}

// Called when the game starts or when spawned
void ABombBase::BeginPlay()
{
	Super::BeginPlay();
   DamageSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
   DamageSphere->SetNotifyRigidBodyCollision(true);
   DamageSphere->SetEnableGravity(true);
   DamageSphere->SetSimulatePhysics(true);
	
   //ProjectileMoveComp->Velocity = FVector(1.0f, 0.0f, 1.0f);
}

// Called every frame
void ABombBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

