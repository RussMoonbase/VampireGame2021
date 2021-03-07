// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/MeleeWeaponBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

AMeleeWeaponBase::AMeleeWeaponBase()
{
   DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
   DamageBox->SetupAttachment(GetRootComponent());
   //DamageBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
   DamageBox->SetNotifyRigidBodyCollision(true);
}

void AMeleeWeaponBase::BeginPlay()
{
   Super::BeginPlay();

   //DamageBox->OnComponentHit.AddDynamic(this, &AMeleeWeaponBase::OnHit);
   DamageBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
   DamageBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeaponBase::OnOverlapImpact);
   //DamageBox->OnComponentEndOverlap
}

void AMeleeWeaponBase::OnOverlapImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   if (!OtherActor)
   {
      return;
   }

   D("Hit by sword!");
   UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, GetOwner(), UDamageType::StaticClass());
}

void AMeleeWeaponBase::OnOverlapImpactEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AMeleeWeaponBase::TurnOnCollision()
{
   D("Turned On Collision");
   DamageBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeaponBase::TurnOffCollision()
{
   DamageBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeaponBase::ThrowSword(FVector direction)
{
   //if (DamageBox)
   //{
   //   DamageBox->SetEnableGravity(true);
   //   DamageBox->SetSimulatePhysics(true);
   //   DamageBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
   //   DamageBox->AddForce(direction * 100000 * DamageBox->GetMass());
   //}
}

//void AMeleeWeaponBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//   if (!OtherActor)
//   {
//      return;
//   }
//
//   D("Hit by sword!");
//
//   UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, GetOwner(), UDamageType::StaticClass());
//
//}
