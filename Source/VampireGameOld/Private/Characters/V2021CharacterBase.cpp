// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/V2021CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AV2021CharacterBase::AV2021CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm
	TheSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TheSpringArm->SetupAttachment(GetRootComponent());

	// Create Camera
	TheCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TheCameraComp->SetupAttachment(TheSpringArm, USpringArmComponent::SocketName);

	// Create skeletal mesh
	//TheSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//TheSkeletalMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AV2021CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AV2021CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AV2021CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

