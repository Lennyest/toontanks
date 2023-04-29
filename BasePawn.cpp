// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Sets the default root component to the capsule component.
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(const FVector &TargetPosition)
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

void ABasePawn::Fire()
{
	DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 10, 6, FColor::Silver, false, 3);
}
