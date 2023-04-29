// Fill out your copyright notice in the Description page of Project Settings.
/**
 * 
 */
#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	bool CheckRange();

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere)
	float MaximumDistance = 800;
	
	UPROPERTY(EditAnywhere)
	float FireRate = 2.0f;
	
	FTimerHandle FireTimerHandle;
	
	void CheckFireCondition();
};
