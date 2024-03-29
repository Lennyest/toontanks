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
	void BeginGame();

	UPROPERTY(EditAnywhere)
	int StartTimer = 3;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
private:
	class ATank* Tank;
	class APawnController* Controller;

	int32 TargetTowers = 0;
	int32 GetTargetTowers();
};
