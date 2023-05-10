// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

// Forward declare them.
class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed = 50.0f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;

	// Value is direction provided by Axis mapping.
	void Move(float Value);
	void Turn(float Value);
	void Rotate(float Value);

	// Storing our last rotation if our result is null.
	FRotator LastRotation;
	APlayerController* TankPlayerController;
};
