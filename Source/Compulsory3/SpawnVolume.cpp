// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "AnimatedEnemy.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bEnemySpawning && !bAnimatedEnemySpawning)
	{
		if (EnemyArray.Num() < 5)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FVector Centre = GetActorLocation();

				float RandX = FMath::FRandRange(Centre.X - 600.f, Centre.X + 600.f);
				float RandY = FMath::FRandRange(Centre.Y - 600.f, Centre.Y + 600.f);
				FVector Location = FVector(RandX, RandY, 100.f);

				tempEnemy = World->SpawnActor<AEnemy>(EnemyBP, Location, FRotator::ZeroRotator);
				EnemyArray.Add(tempEnemy);
			}
		}
		for (int i{}; i < EnemyArray.Num(); i++)
		{
			if (EnemyArray[i]->bDead)
			{
				EnemyArray[i]->Destroy();
				EnemyArray.RemoveAt(i);
			}
		}
	}

	if (!bEnemySpawning && bAnimatedEnemySpawning)
	{
		if (AnimatedEnemyArray.Num() < 5)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FVector Centre = GetActorLocation();

				float RandX = FMath::FRandRange(Centre.X - 600.f, Centre.X + 600.f);
				float RandY = FMath::FRandRange(Centre.Y - 600.f, Centre.Y + 600.f);
				FVector Location = FVector(RandX, RandY, 100.f);

				tempAnimatedEnemy = World->SpawnActor<AAnimatedEnemy>(AnimatedEnemyBP, Location, FRotator::ZeroRotator);
				AnimatedEnemyArray.Add(tempAnimatedEnemy);
			}
		}
		for (int i{}; i < AnimatedEnemyArray.Num(); i++)
		{
			if (AnimatedEnemyArray[i]->bDead)
			{
				AnimatedEnemyArray[i]->Destroy();
				AnimatedEnemyArray.RemoveAt(i);
			}
		}
	}

}

