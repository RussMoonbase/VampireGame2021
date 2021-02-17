// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

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

	DamageSphere->OnComponentBeginOverlap.AddDynamic(this, &ABulletBase::OnOverlapImpact);
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::OnOverlapImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   if (!OtherActor)
   {
      return;
   }

   D("Hit by bullet!");
   UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, GetOwner(), UDamageType::StaticClass());

	OnImpact(SweepResult);
}

