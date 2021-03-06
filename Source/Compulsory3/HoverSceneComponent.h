// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class COMPULSORY3_API UHoverSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float TraceLength;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float HoverForce;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float LinearDamping;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float AngularDamping;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	FHitResult HitResult;

public:	
	// Sets default values for this component's properties
	UHoverSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float LinearDampingDefault = 25.f;
	float AngularDampingDefault = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HoverVariables")
	class APlayerCar* PlayerCar;
};
