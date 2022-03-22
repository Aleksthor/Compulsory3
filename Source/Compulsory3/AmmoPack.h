// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPack.generated.h"

UCLASS()
class COMPULSORY3_API AAmmoPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoPackVariables")
	class UBoxComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoPackVariables")
	class UStaticMeshComponent* AmmoPackMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoPackVariables")
	int AmmoGiven;

	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
