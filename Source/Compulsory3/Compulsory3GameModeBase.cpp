// Copyright Epic Games, Inc. All Rights Reserved.


#include "Compulsory3GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

ACompulsory3GameModeBase::ACompulsory3GameModeBase()
{

}

void ACompulsory3GameModeBase::BeginPlay()
{

	Super::BeginPlay();

	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	float EnemyAmount = 5;
	//	for (int i{}; i < EnemyAmount; i++)
	//	{
	//		float RandX = FMath::FRandRange(-10000.f, 10000.f);
	//		float RandY = FMath::FRandRange(-10000.f, 10000.f);
	//		FVector Location = FVector(RandX, RandY, 100.f);

	//		tempEnemy = World->SpawnActor<AEnemy>(EnemyBP, Location, FRotator::ZeroRotator);
	//		EnemyArray.Add(tempEnemy);
	//		
	//	}
	//}
}

void ACompulsory3GameModeBase::Tick(float DeltaSeconds)
{

}

void ACompulsory3GameModeBase::LoadMap1()
{
	FName Level1 = FName("Map");
	UGameplayStatics::OpenLevel(GetWorld(), Level1);
}

void ACompulsory3GameModeBase::LoadMap2()
{
	FName Level2 = FName("Map2");
	UGameplayStatics::OpenLevel(GetWorld(), Level2);
}
