// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPack.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"

// Sets default values
AAmmoPack::AAmmoPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPack::OnOverlap);

	AmmoPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBoostMesh"));
	AmmoPackMesh->SetupAttachment(Collider);

	
}

// Called when the game starts or when spawned
void AAmmoPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AAmmoPack::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* PlayerCar = Cast<APlayerCar>(OtherActor);
	if (PlayerCar)
	{
		AmmoGiven = PlayerCar->InitialAmmo;
		PlayerCar->Ammo += AmmoGiven;
		PlayerCar->AmmoRecieved = AmmoGiven;
		PlayerCar->bSetVisibleOnHUD = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}
}

