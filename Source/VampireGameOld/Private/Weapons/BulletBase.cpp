// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
   SetRootComponent(DamageSphere);
   DamageSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(DamageSphere);
	
	if (GetOwner())
	{
		MeshComp->IgnoreActorWhenMoving(GetOwner(), true);
	}
	
	if (GetOwner() && GetOwner()->GetOwner())
	{
		MeshComp->IgnoreActorWhenMoving(GetOwner()->GetOwner(), true);
	}

	ProjecticleMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));
	ProjecticleMoveComp->InitialSpeed = 3000;
	ProjecticleMoveComp->Velocity = FVector(1.0f, 0.0f, 0.0f);

}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

