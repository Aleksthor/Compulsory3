// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class COMPULSORY3_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	class USphereComponent* AttackCollider{ nullptr };

	// Controller that gives AI inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyVariables")
	class AAIController* AIController{ nullptr };


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
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);


	/** Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float Health = 100.f;
};
