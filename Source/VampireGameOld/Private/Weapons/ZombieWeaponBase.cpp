// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ZombieWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "VampireGameOld/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"

// Sets default values
AZombieWeaponBase::AZombieWeaponBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp = GetCapsuleComponent();
	
}

// Called every frame
void AZombieWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombieWeaponBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombieWeaponBase::AddDamage(AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}

   AEnemy* TheEnemy = Cast<AEnemy>(OtherActor);
   USkeletalMeshComponent* EnemySkeletalMeshComp = nullptr;

   if (TheEnemy)
   {
      EnemySkeletalMeshComp = TheEnemy->GetEnemySkeletalMesh();
   }
	UGameplayStatics::ApplyDamage(this, DamageAmount, nullptr, GetOwner(), UDamageType::StaticClass());
	UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, nullptr, GetOwner(), UDamageType::StaticClass());

	if (EnemySkeletalMeshComp)
	{
		EnemySkeletalMeshComp->AddRadialImpulse(GetActorLocation(), 300.0f, 150.0f, ERadialImpulseFalloff::RIF_Constant, true);
	}

}

void AZombieWeaponBase::RagdollDeath()
{
	AAIController* theAIController = Cast<AAIController>(GetController());

	if (theAIController)
	{
		theAIController->UnPossess();
	}

   GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
   GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("Root"), true);
   GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(FName("Root"), 1);

	GetMesh()->AddRadialImpulse(GetActorLocation(), 300.0f, 150.0f, ERadialImpulseFalloff::RIF_Constant, true);

   if (CapsuleComp)
   {
      CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
   }
}

