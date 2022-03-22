// Fill out your copyright notice in the Description page of Project Settings.


#include "GateWayToLevel2.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGateWayToLevel2::AGateWayToLevel2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGateWayToLevel2::OnOverlap);
}

// Called when the game starts or when spawned
void AGateWayToLevel2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGateWayToLevel2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateWayToLevel2::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayerCar>())
	{
		FName Level2 = FName("Map2");
		UGameplayStatics::OpenLevel(GetWorld(), Level2);
	}

}

