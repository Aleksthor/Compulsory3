// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class AEnemy;
class AAnimatedEnemy;

UCLASS()
class COMPULSORY3_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Ideally id like to notice how many enemies are inside, so i can spawn more accordingly
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnVolumeVariables")
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnVolumeVariables", meta = (MustImplement = "ActionInterface"))
	TSubclassOf<AEnemy> EnemyBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnVolumeVariables", meta = (MustImplement = "ActionInterface"))
	TSubclassOf<AAnimatedEnemy> AnimatedEnemyBP;

	TArray<class AEnemy*> EnemyArray;
	AEnemy* tempEnemy;

	TArray<class AAnimatedEnemy*> AnimatedEnemyArray;
	AAnimatedEnemy* tempAnimatedEnemy;

	/** Do not have both booleans active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnVolumeVariables",meta = (MustImplement = "ActionInterface"))
	bool bEnemySpawning = false;

	/** Do not have both booleans active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnVolumeVariables", meta = (MustImplement = "ActionInterface"))
	bool bAnimatedEnemySpawning = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
