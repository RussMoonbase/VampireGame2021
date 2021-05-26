// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BombBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VampireGameOld/Enemy.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan , TEXT(x));}

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
   DamageSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
   DamageSphere->SetNotifyRigidBodyCollision(true);
   DamageSphere->SetEnableGravity(true);
   DamageSphere->SetSimulatePhysics(true);

   DamageSphere->OnComponentHit.AddDynamic(this, &ABombBase::OnImpact);
   bBombHasHit = false;
   //ProjectileMoveComp->Velocity = FVector(1.0f, 0.0f, 1.0f);
}

// Called every frame
void ABombBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombBase::OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
   if (!bBombHasHit)
   {
      bBombHasHit = true;
      OnHit(Hit);
      AddExplosiveForce();
   }
}

void ABombBase::AddExplosiveForce()
{
   TArray<FHitResult> HitResults;

   FVector BombLocation = GetActorLocation();

   FVector Start = BombLocation;
   FVector End = BombLocation;

   FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(100.0f);

   //DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionSphere.GetSphereRadius(), 50, FColor::Orange, true);

   bool isHitBySweep = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_WorldStatic, ExplosionSphere);

   if (isHitBySweep)
   {
      for (FHitResult theHitResult : HitResults)
      {
         if (theHitResult.GetActor())
         {
            //UCapsuleComponent* HitCapsuleComp = Cast<UCapsuleComponent>(theHitResult.GetActor()->GetRootComponent());
            AEnemy* TheEnemy = Cast<AEnemy>(theHitResult.GetActor());
            USkeletalMeshComponent* HitSkeletalMeshComp = nullptr;
            if (TheEnemy)
            {
               HitSkeletalMeshComp = TheEnemy->GetEnemySkeletalMesh();
            }

            UGameplayStatics::ApplyDamage(theHitResult.GetActor(), 25.0f, nullptr, GetOwner(), UDamageType::StaticClass());

            if (HitSkeletalMeshComp)
            {
               HitSkeletalMeshComp->AddRadialImpulse(GetActorLocation(), 300.0f, 150.0f, ERadialImpulseFalloff::RIF_Constant, true);
            }

            //if (HitCapsuleComp)
            //{
            //   D("Hit actor mesh");
            //   
            //   HitCapsuleComp->SetSimulatePhysics(true);
            //   HitCapsuleComp->AddRadialImpulse(GetActorLocation(), 300.0f, 100.0f, ERadialImpulseFalloff::RIF_Constant, true);
            //}
         }

      }
   }
}

