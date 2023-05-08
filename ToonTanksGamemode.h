// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGamemode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* ActorDied);
protected:
	virtual void BeginPlay() override;
private:
	class ATank* Tank;
};
