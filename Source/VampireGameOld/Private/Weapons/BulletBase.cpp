// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BulletBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Characters/V2021PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "VampireGameOld/Enemy.h"
#include "Weapons/BombBase.h"
#include "Kismet/KismetMathLibrary.h"

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

	AV2021PlayerCharacter* PlayerCharacter = Cast<AV2021PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter)
	{
		if (PlayerCharacter->GetLockedOnEnemy())
		{
			LockedOnEnemy = PlayerCharacter->GetLockedOnEnemy();
		}
	}
	else
	{
		LockedOnEnemy = nullptr;
	}

	EnemyProximityDistance *= EnemyProximityDistance;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Enemy Proximity Distance = %f"), EnemyProximityDistance));

	bTargetReached = false;
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockedOnEnemy)
	{
		FVector theEnemyVector = FVector(LockedOnEnemy->GetActorLocation().X, LockedOnEnemy->GetActorLocation().Y, 0.0f);
		FVector theBulletVector = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, 0.0f);
		//targetDistance = (LockedOnEnemy->GetActorLocation() - this->GetActorLocation()).SizeSquared();
		targetDistance = (theEnemyVector - theBulletVector).SizeSquared();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Bullet Distance to Target = %f"), targetDistance));

		if (targetDistance < EnemyProximityDistance && !bTargetReached)
		{
			bTargetReached = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Target reached")));
			OnTargetReached(this->GetActorLocation());
		}
	}


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

void ABulletBase::SpawnMicroBombs()
{
	float radius = 128.0f;
	FTransform SpawnLocation = this->GetTransform();

	for (int i = 0; i < 8; i++)
	{
		float angle = ((2 * UKismetMathLibrary::GetPI()) * i) / 8;
		FVector spawnVector = FVector(UKismetMathLibrary::Cos(angle), UKismetMathLibrary::Sin(angle), 0.0f);
		FVector finalSpawnPosition = SpawnLocation.GetLocation() + spawnVector * radius;
		FRotator theRotation = this->GetActorRotation();
		GetWorld()->SpawnActor<ABombBase>(MicroBomb, finalSpawnPosition, theRotation);
	}

}

