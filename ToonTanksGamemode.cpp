// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGamemode.h"

#include "PawnController.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGamemode::ActorDied(AActor* ActorDied)
{
	if (!ActorDied )
	{
		UE_LOG(LogType, Display, TEXT("The actor does not exist, returning."));
	}

	if (!Tank)
	{
		UE_LOG(LogType, Display, TEXT("The tank does not exist, returning."));
	}
	
	if (ActorDied == Tank)
	{
		Tank->HandleDestruction();
		if (Controller)
		{
			Controller->SetPlayerEnabledState(false);
		}
	}
	else if (ATower* Tower = Cast<ATower>(ActorDied))
	{
		Tower->HandleDestruction();
	}
}

void AToonTanksGamemode::BeginGame()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	Controller = Cast<APawnController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (Controller)
	{
		Controller->SetPlayerEnabledState(false);

		// Enables controller input after three seconds.
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(Controller, &APawnController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartTimer, false);
	}
}

void AToonTanksGamemode::BeginPlay()
{
	Super::BeginPlay();
	BeginGame();
}
