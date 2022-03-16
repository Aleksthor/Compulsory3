// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "PlayerCar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Bullet.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollider"));
	AttackCollider->SetupAttachment(RootComponent);
	AttackCollider->InitSphereRadius(2500.f);
	
	
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// This character will get assigned a controller when we press play , Because its a character
	AIController = Cast<AAIController>(GetController());
	
	// Didnt work in Constructor
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
	AttackCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShooting)
	{
		ShootClock += DeltaTime;
		
		
		if (ShootClock > ShootTimer)
		{
			ShootClock = 0.f;

			GetWorld()->SpawnActor<ABullet>(BulletBP, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorForwardVector().Rotation());
		}
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("MovingToPlayer"));
		AIController->MoveToActor(Player, 500.f);
		AIController->SetFocus(Player);
		bShooting = true;
	}
}

void AEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (AIController && Player)
	{
		AIController->StopMovement();
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
		bShooting = false;
		ShootClock = 0.f;
	}
}

