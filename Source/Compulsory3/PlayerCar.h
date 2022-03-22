// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

class ABullet; 
class UHoverSceneComponent;

UCLASS()
class COMPULSORY3_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar();

	/** Component Body */
	/** Static Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class UStaticMeshComponent* PlayerMesh{ nullptr };

	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class UBoxComponent* Collider{ nullptr };

	/** Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class USpringArmComponent* SpringArm{ nullptr };

	/** Camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class UCameraComponent* Camera{ nullptr };

	//** MovementComponent */
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverSceneComponent* HoverComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverSceneComponent* HoverComponent2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverSceneComponent* HoverComponent3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverSceneComponent* HoverComponent4;
	/** Bullets not active in project yet */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerVariables")
	TSubclassOf<ABullet> BulletBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	int Ammo;

	int InitialAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	float Health = 100.f;

	float DriftValue;

	// How often we shoot full auto
	float ShootSpeed = 1.f;

	// Start to shoot right away the first shot
	float ShootClock = 1.f;

	// Save Pawn Rotation Every Tick
	FRotator PawnRotation;

	// Save Control Rotation Every Tick
	FRotator ControlRotation;

	// Save Control Rotation Every Tick
	FRotator NewRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	FString AmmoPack{ "" };

	int AmmoRecieved = 0;

	bool bSetVisibleOnHUD = false;
	float HUDTimer = 2.f;
	float HUDClock = 0.f;

	/** Functions */

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void StartShooting();

	UFUNCTION()
	void StopShooting();

	UFUNCTION()
	void Forward(float value);

	UFUNCTION()
	void Right(float value);

	UFUNCTION()
	void StartDrift();

	UFUNCTION()
	void StopDrift();

	UFUNCTION()
	void Reload();


	/** Booleans */

	bool bShooting = false;

	bool bDrifting = false;

	bool bRight = false;
};
