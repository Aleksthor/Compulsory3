// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class ABullet;
class USphereComponent;
class AAmmoPack;


UCLASS()
class COMPULSORY3_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	USphereComponent* AttackCollider{ nullptr };

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	USphereComponent* HealthCollider{ nullptr };

	// Controller that gives AI inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	class AAIController* AIController{ nullptr };
		
	/** Bullets not active in project yet */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemyVariables")
	TSubclassOf<ABullet> BulletBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemyVariables")
	TSubclassOf<AAmmoPack> AmmoPackBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemyVariables")
	bool bSetVisibility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Functions */

	UFUNCTION()
	void OnOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
		void OnOverlapHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEndHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	bool bShooting = false;

	bool bAttacking = false;

	bool Spawned = false;

	bool bDead = false;

	/** Variables */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	float Health;	

	float ShootTimer = 1.f;

	float ShootClock = 0.f;

	float RoamTimer = 4.f;
	float RoamClock = 0.f;
};
