// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Compulsory3GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COMPULSORY3_API ACompulsory3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ACompulsory3GameModeBase();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void LoadMap1();

	UFUNCTION(BlueprintCallable)
	void LoadMap2();


	TArray<class AEnemy*> EnemyArray;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemy> EnemyBP;

	AEnemy* tempEnemy;
	
};
