// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FingerGun.h"
#include "Components/ArrowComponent.h"
#include "Weapons/BulletBase.h"

// Sets default values
AFingerGun::AFingerGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bullet = ABulletBase::StaticClass();

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	GunMuzzleArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("GunMuzzle"));
	GunMuzzleArrow->SetupAttachment(RootComp);
	GunMuzzleArrow->ArrowSize = 0.3f;
	GunMuzzleArrow->ArrowColor = FColor::Yellow;
}

// Called when the game starts or when spawned
void AFingerGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFingerGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFingerGun::StartShooting_Implementation()
{
	if (!Bullet)
	{
		return;
	}

	if (CurrentAmmo > 0)
	{
		//AActor* BulletOwner = GetOwner() ? GetOwner() : this;
		const FTransform SpawnTransform = GunMuzzleArrow->GetComponentTransform();

		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(Bullet, SpawnTransform, Params);


	}
}

void AFingerGun::StopShooting_Implementation()
{

}

