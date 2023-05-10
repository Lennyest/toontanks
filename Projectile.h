// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, Category="Tank")
	float InitialSpeed = 1300.;
	UPROPERTY(EditAnywhere, Category="Tank")
	float MaxSpeed = 1300.;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category="Tank")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Tank", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category="Tank", meta=(AllowPrivateAccess="true"))
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, Category="Tank")
	float Damage = 50.;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShake;
};
