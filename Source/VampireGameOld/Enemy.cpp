// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"


#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan , TEXT(x));}
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp = GetCapsuleComponent();
	gameTime = 0.0f;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLevitating)
	{
		gameTime = gameTime + DeltaTime;

		FVector NewLocation = GetActorLocation();
		float newHeight = FMath::Sin(gameTime);
		float zOffset = 1.0f * newHeight;
		NewLocation.Z += zOffset;
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::ActivateLevitate()
{
	D("Levitate called");
	if (CapsuleComp)
	{
		D("Found Capsule Component");
		CapsuleComp->SetEnableGravity(false);
		CapsuleComp->SetSimulatePhysics(false);
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//FVector NewLocation = GetActorLocation();
		bIsLevitating = true;
	}
}

