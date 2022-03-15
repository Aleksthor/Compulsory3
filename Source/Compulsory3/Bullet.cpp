// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Collider = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollider"));
    SetRootComponent(Collider);
    Collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
    Collider->InitSphereRadius(15.f);
    Collider->SetGenerateOverlapEvents(true);

    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
    BulletMesh->SetupAttachment(Collider);
    BulletMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Bullet will go forward in a straight line
    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * DeltaTime;
    SetActorLocation(NewLocation);

    // If too long time pass we kill the bullet
    TimeLived += DeltaTime;
    if (TimeLived > TimeBeforeDestroy)
    {
        this->Destroy();
    }

}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor->IsA<ABullet>())
    {
        UE_LOG(LogTemp, Warning, TEXT("OtherActor->Bullet"));
        //Cast<ABullet>(OtherActor)->DestroyBullet();
        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);
    }
}

void ABullet::DestroyBullet()
{
    UE_LOG(LogTemp, Warning, TEXT("DestroyBullet"));
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}

