// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

bool ATower::CheckRange()
{
	if (!Tank) return false;

	if (const float Distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation()); Distance > MaximumDistance) return false;

	FHitResult Result;
	const bool Hit = GetWorld()->LineTraceSingleByChannel(
		Result,
		ProjectileSpawnPoint->GetComponentLocation(),
		Tank->GetActorLocation(),
		ECC_Visibility
	);
	
	return Hit && Result.GetActor() == UGameplayStatics::GetPlayerPawn(this, 0) && Result.ImpactPoint != FVector::Zero();
}

void ATower::CheckFireCondition()
{
	if (CheckRange())
	{
		Fire();
	}
}
