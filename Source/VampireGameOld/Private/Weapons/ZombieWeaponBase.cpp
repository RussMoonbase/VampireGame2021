// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ZombieWeaponBase.h"
#include "Kismet/GameplayStatics.h"

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

	UGameplayStatics::ApplyDamage(OtherActor, 300.0f, nullptr, GetOwner(), UDamageType::StaticClass());
}

