// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::Rotate);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult Result;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, Result);

		DrawDebugSphere(GetWorld(), Result.ImpactPoint, 10, 6, FColor::Red, false, 1);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::RotateTurret(FVector TargetPosition)
{
	// Do not handle rotation if our result is 0!
	if (TargetPosition == FVector::Zero()) return;
	
	const FRotator TargetRotation = (GetActorLocation() - TargetPosition).Rotation();
	const FRotator TurretRotation = FRotator(0, TargetRotation.Yaw + 180, 0);

	LastRotation = TurretRotation;
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			TurretRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			RotationSpeed)
		);
}

void ATank::Move(const float Value)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const float Value)
{
	FRotator DeltaRotation(0.);
	DeltaRotation.Yaw = Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::Rotate(float Value)
{
	if (!PlayerControllerRef) return;
	
	FHitResult Result;
	PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, Result);

	RotateTurret(Result.ImpactPoint);
}
