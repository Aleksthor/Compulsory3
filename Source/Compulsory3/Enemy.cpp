// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "PlayerCar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Bullet.h"
#include "PlayerCar.h"
#include "AmmoPack.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollider"));
	AttackCollider->SetupAttachment(RootComponent);
	AttackCollider->InitSphereRadius(4000.f);

	HealthCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HealthCollider"));
	HealthCollider->SetupAttachment(RootComponent);
	

	
	Health = 100.f;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// This character will get assigned a controller when we press play , Because its a character
	AIController = Cast<AAIController>(GetController());
	
	bSetVisibility = false;

	RoamClock = FMath::RandRange(0.f, RoamTimer);
	// Didnt work in Constructor
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapAttack);
	AttackCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEndAttack);

	HealthCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapHealth);
	HealthCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEndHealth);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Some Random Movement if enemy is not targeting player
	FVector CurrentLocation = GetActorLocation();
	if (!bAttacking)
	{
		RoamClock += DeltaTime;

		if (RoamClock > RoamTimer)
		{
			FVector Rand = FVector(0.f,0.f,100.f);
			Rand.X = FMath::FRandRange(CurrentLocation.X - 1500.f, CurrentLocation.X + 1500.f);
			Rand.Y = FMath::FRandRange(CurrentLocation.Y - 1500.f, CurrentLocation.Y + 1500.f);

			AIController->MoveTo(Rand);
			RoamClock = 0.f;
		}
	}
	

	if (bShooting)
	{
		ShootClock += DeltaTime;
		
		
		if (ShootClock > ShootTimer)
		{
			ShootClock = 0.f;
			APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
			FVector PlayerLocation = Cast<APlayerCar>(Player)->GetActorLocation();
			FVector EnemyLocation = GetActorLocation();
			FVector ShootVector = PlayerLocation - EnemyLocation;
			GetWorld()->SpawnActor<ABullet>(BulletBP, GetActorLocation() + GetActorForwardVector() * 100.f, ShootVector.Rotation());
		}
	}


	if ((FMath::IsNearlyEqual(Health, 0.f) && !Spawned) || (Health < 0.f && !Spawned))
	{
		
		Spawned = true;
		GetWorld()->SpawnActor<AAmmoPack>(AmmoPackBP, GetActorLocation(), GetActorRotation());
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		bDead = true;
	}
	
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player && AIController)
	{
		bAttacking = true;
		AIController->MoveToActor(Player, 500.f);
		AIController->SetFocus(Player);
		bSetVisibility = true;
		bShooting = true;
	}
}

void AEnemy::OnOverlapEndAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (AIController && Player)
	{
		bAttacking = false;
		AIController->StopMovement();
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
		bShooting = false;
		ShootClock = 0.f;
		bSetVisibility = false;
	}
	
}

void AEnemy::OnOverlapHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA<ABullet>())
	{
		Health -= 20.f;
		//UE_LOG(LogTemp,Warning,TEXT("Enemy Hit Health Left: %f"),Health)
	}
}

void AEnemy::OnOverlapEndHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

