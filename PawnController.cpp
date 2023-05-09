// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnController.h"

void APawnController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	
	bShowMouseCursor = bPlayerEnabled;
}
