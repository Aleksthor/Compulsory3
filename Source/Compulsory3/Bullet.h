// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class COMPULSORY3_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	/** Collider */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletVariables")
	class USphereComponent* Collider;

	/** Bullet Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletVariables")
	class UStaticMeshComponent* BulletMesh;

	/** How fast the bullet moves */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletVariables")
	float Speed = 5000.f;

	/** How many seconds before it's destroyed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletVariables")
	float TimeBeforeDestroy = 5.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	/** Function run when bullet hits something */
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	/** If bullet hits something that destroys itself, also destroy bullet */
	UFUNCTION()
	void DestroyBullet();

	/** Timer start at 0 */
	float TimeLived = 0.f;
};
