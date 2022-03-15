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

	UFUNCTION(BlueprintCallable)
	void LoadMap1();

	UFUNCTION(BlueprintCallable)
	void LoadMap2();
	
};
