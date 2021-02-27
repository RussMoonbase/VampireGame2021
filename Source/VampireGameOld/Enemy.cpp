// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/V2021PlayerCharacter.h"
#include "Blueprint/UserWidget.h"


#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan , TEXT(x));}
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dimensions = FVector(100, 0, 0);
	AxisVector = FVector(0, 0, 1);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp = GetCapsuleComponent();
	gameTime = 0.0f;

	// set bCanBePickedUpToFalse for initial pickup
	bCanBePickedUp = true;

	// enemy is NOT dead on begin play
	bIsDead = false;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartFloating)
	{
		FloatEnemy(DeltaTime);
	}

	//if (bIsLevitating)
	//{
	//	Levitate(DeltaTime);
	//}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// turns on levitate so enemy begins moving up after death and player pick up attack
void AEnemy::ActivateLevitate()
{
	D("Levitate called");
	if (CapsuleComp)
	{
		D("Found Capsule Component");
		CapsuleComp->SetEnableGravity(false);
		CapsuleComp->SetSimulatePhysics(false);
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FVector OriginalLocation = GetActorLocation();
		OrginalZLocationBeforeLevitate = OriginalLocation.Z;
		bStartFloating = true;
	}
}

void AEnemy::SetEnemyLevitateNumber(int theNum)
{
	if (theNum < 4 && theNum > 0)
	{
		EnemyLevitateNumber = theNum;
	}
}

void AEnemy::FlingDownedEnemy(FVector ForwardVector)
{
	bIsLevitating = false;
   CapsuleComp->SetEnableGravity(true);
   CapsuleComp->SetSimulatePhysics(true);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComp->AddForce(ForwardVector * 100000 * CapsuleComp->GetMass());
}

bool AEnemy::GetbCanBePickedUp()
{
	return bCanBePickedUp;
}

void AEnemy::SetbCanBePickedUp(bool booleanValue)
{
	bCanBePickedUp = booleanValue;
}

bool AEnemy::GetbStartFloating()
{
	return bStartFloating;
}

void AEnemy::FloatEnemy(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();

	if (NewLocation.Z < OrginalZLocationBeforeLevitate + 45.0f)
	{
		NewLocation.Z += 10.0f * DeltaTime;
      SetActorLocation(NewLocation);
	}
	else
	{
		bStartFloating = false;
		bIsLevitating = true;
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		float XValue = GetActorLocation().X - PlayerLocation.X;
      float YValue = GetActorLocation().Y - PlayerLocation.Y;
		Dimensions = FVector(XValue, YValue, 0);
		PlayerCharacter = Cast<AV2021PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (PlayerCharacter)
		{
			PlayerCharacter->ActivateSoulSphere(EnemyLevitateNumber);
		}
		
		if (GetMesh())
		{
			GetMesh()->SetVisibility(false);
		}
	}

}

void AEnemy::Levitate(float DeltaTime)
{
   gameTime = gameTime + DeltaTime;

   //FVector NewLocation = GetActorLocation();
   //float newHeight = FMath::Sin(gameTime);
   //float zOffset = 1.0f * newHeight;
   //NewLocation.Z += zOffset;
	//SetActorLocation(NewLocation);

	FVector TheLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	AngleAxis += DeltaTime * 5.0f;

	if (AngleAxis >= 360.0f)
	{
		AngleAxis = 0;
	}

	FVector RotateValue = Dimensions;

	TheLocation.X += RotateValue.X;
	TheLocation.Y += RotateValue.Y;
	//FVector NewLocation = GetActorLocation();
	FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	NewLocation.Z += 45.0f;

   float newHeight = FMath::Sin(gameTime);
	float zOffset = 20.0f * newHeight;
	//UE_LOG(LogTemp, Warning, TEXT("%f"),zOffset);
	NewLocation.Z += zOffset;
	TheLocation.Z = NewLocation.Z;

   SetActorLocation(TheLocation, false, 0, ETeleportType::None);
}

