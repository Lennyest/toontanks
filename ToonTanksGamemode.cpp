// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGamemode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGamemode::ActorDied(AActor* ActorDied)
{
	if (Tank && ActorDied == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}
	}
	else if (ATower* Tower = Cast<ATower>(ActorDied))
	{
		Tower->HandleDestruction();
	}
}

void AToonTanksGamemode::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
