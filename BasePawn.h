// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 25.0f;

	void HandleDestruction();
	
protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;

	void RotateTurret(const FVector& TargetPosition);
	void Fire();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank", meta=(AllowPrivateAccess="true"))
	USceneComponent* ProjectileSpawnPoint;
	
private:
	// The use of the allowprivateaccess meta tag is silly, ideally you would place these in the public section instead...
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	
	FRotator LastRotation;
};
