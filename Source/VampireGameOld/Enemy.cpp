// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Characters/V2021PlayerCharacter.h"
#include <Components/WidgetComponent.h>
#include "Characters/TargetDot.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/DamageType.h"
#include "Math/Vector.h"
#include "Perception/AISense_Hearing.h"
#include "Components/SphereComponent.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan , TEXT(x));}
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dimensions = FVector(100, 0, 0);
	AxisVector = FVector(0, 0, 1);

	TargetWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetDotComp"));
	TargetWidgetComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));

	if (GetMesh())
	{
		DamageSphere->SetupAttachment(GetMesh());
	}
	DamageSphere->SetNotifyRigidBodyCollision(true);
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

	// turn off target dot widget
	TargetWidgetComp->SetVisibility(false);

	DamageSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartFloating)
	{
		FloatEnemy(DeltaTime);
	}

	if (bIsDead)
	{
		CapsuleFollowRagdoll();
	}

   //if (bIsLevitating)
   //{
   //   Levitate(DeltaTime);
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
		CapsuleComp->SetEnableGravity(false);
		CapsuleComp->SetSimulatePhysics(false);
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	bIsDead = false;
   PlayerCharacter = Cast<AV2021PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

   if (GetMesh())
   {
      GetMesh()->SetVisibility(false);
		GetMesh()->SetSimulatePhysics(false);
      GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
   }

   if (PlayerCharacter)
   {
      PlayerCharacter->ActivateSoulSphere(EnemyLevitateNumber);
      //PlayerCharacter->EquipLevitatingEnemy(this);
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
	bIsShotRagdoll = true;

	if (bIsShotRagdoll)
	{
		OnShotByPlayer.Broadcast();
	}

	if (PlayerCharacter)
	{
		PlayerCharacter->DeactivateSoulSphere(EnemyLevitateNumber);
		PlayerCharacter->UnequipLevitatingEnemy(this);
	}

   if (GetMesh())
   {
		//GetMesh()->OnComponentHit.AddDynamic(this, &AEnemy::OnRagdollImpact);
      GetMesh()->SetVisibility(true);
      bIsLevitating = false;
      GetMesh()->SetCollisionProfileName(TEXT("ShotRagdoll"));
      GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("Hips"), true);
      GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(FName("Hips"), 1);
      GetMesh()->AddForce(ForwardVector * 100000 * GetMesh()->GetMass());
   }



	//bIsLevitating = false;
 //  CapsuleComp->SetEnableGravity(true);
 //  CapsuleComp->SetSimulatePhysics(true);
	//CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CapsuleComp->AddForce(ForwardVector * 100000 * CapsuleComp->GetMass());
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

// set the visibility of the target dot when player turns on Z targeting
void AEnemy::SetTargetDotVisibility(bool booleanValue)
{
	if (TargetWidgetComp)
	{
		TargetWidgetComp->SetVisibility(booleanValue);
	}
}

// activate right side hit animation
void AEnemy::RightSideHit()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && HitMontage)
	{
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactFromRight"), HitMontage);
	}
}

void AEnemy::LeftSideHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactFromLeft"), HitMontage);
   }
}

void AEnemy::FrontStomachHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactFromFront"), HitMontage);
   }
}

void AEnemy::BackHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactFromBack"), HitMontage);
   }
}

void AEnemy::TopHeadHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactTopHead"), HitMontage);
   }
}

void AEnemy::LeftLegHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactLeftLeg"), HitMontage);
   }
}

void AEnemy::RightLegHit()
{
   UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

   if (AnimInstance && HitMontage)
   {
      AnimInstance->Montage_Play(HitMontage, 1.25f);
      AnimInstance->Montage_JumpToSection(FName("ReactRightLeg"), HitMontage);
   }
}

void AEnemy::DeathRagdoll()
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("Root"), true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(FName("Root"), 1);

	if (CapsuleComp)
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	}
	bIsDead = true;
}

void AEnemy::EndOfDeath()
{
	GetMesh()->bPauseAnims = true;
	//GetMesh()->bNoSkeletonUpdate = true;
   //if (CapsuleComp)
   //{
   //	CapsuleComp->SetEnableGravity(false);
   //	CapsuleComp->SetSimulatePhysics(false);
   //	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
   //}

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}

void AEnemy::RagdollHit(AActor* OtherActor)
{
	if (!OtherActor)
	{
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor, 300.0f, nullptr, GetOwner(), UDamageType::StaticClass());
}

// blueprint callable to be used to check if enemy was shot out as ragdoll
bool AEnemy::GetIsShotRagdoll()
{
	return bIsShotRagdoll;
}

void AEnemy::CapsuleFollowRagdoll()
{
	if (GetMesh() && CapsuleComp)
	{
		FVector newCapsuleLocation = GetMesh()->GetSocketLocation(FName("Root"));
		newCapsuleLocation.Z = newCapsuleLocation.Z + 89.132126f;
		CapsuleComp->SetWorldLocation(newCapsuleLocation);
	}
}

void AEnemy::RemoveFromScene()
{
	Destroy();
}

USkeletalMeshComponent* AEnemy::GetEnemySkeletalMesh()
{
	return GetMesh();
}

void AEnemy::TurnOnNoiseTracking(bool booleanValue)
{
	if (booleanValue)
	{
		D("NOISE ADDED");
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.0f, this, 0.0f);
	}
}

//void AEnemy::OnRagdollImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (!OtherActor)
//	{
//		return;
//	}
//
//   D("Hit by flying ragdoll!");
//   UGameplayStatics::ApplyDamage(OtherActor, 300.0f, nullptr, GetOwner(), UDamageType::StaticClass());
//}

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
		//bIsLevitating = true;
		//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
      //float XValue = GetActorLocation().X - PlayerLocation.X;
      //float YValue = GetActorLocation().Y - PlayerLocation.Y;
      //Dimensions = FVector(XValue, YValue, 0);
		PlayerCharacter = Cast<AV2021PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (GetMesh())
		{
			GetMesh()->SetVisibility(false);
			GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		}

      if (PlayerCharacter)
      {
         PlayerCharacter->ActivateSoulSphere(EnemyLevitateNumber);
			PlayerCharacter->EquipLevitatingEnemy(this);
      }

		//CapsuleComp->SetSimulatePhysics(true);
		//CapsuleComp->SetCollisionProfileName(TEXT("OverlapAll"));
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

