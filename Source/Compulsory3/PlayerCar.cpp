// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Bullet.h"



// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Collider Default Values */
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->SetSimulatePhysics(true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCar::OnOverlap);
	

	/** Player Mesh Default Values */
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(Collider);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StaticMesh/SciFighter/SciFi_Fighter_AK5_SciFi_Fighter_AK5.SciFi_Fighter_AK5_SciFi_Fighter_AK5'"));
	PlayerMesh->SetStaticMesh(Mesh.Object);
	PlayerMesh->SetRelativeScale3D(FVector(0.1f, 0.15f, 0.15f));
	PlayerMesh->SetRelativeLocation(FVector(0.f, -23.f, 0.f));

	/** Spring Arm Default Values */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetupAttachment(PlayerMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;

	/** Movement Component Default Values*/
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = Collider;
	

	/** Attaching Camera to the SpringArm*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);



	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Ammo = InitialAmmo;
}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PawnRotation = GetActorRotation();
	ControlRotation = GetControlRotation();



	if (!MovementComponent->Velocity.IsNearlyZero())
	{
		PawnRotation = GetActorRotation();
		FRotator Yaw = FMath::RInterpTo(PawnRotation, ControlRotation, DeltaTime, 5.f);
		if (MovementComponent->IsFalling())
		{
			UE_LOG(LogTemp, Warning, TEXT("Falling"));
			FRotator PitchRoll = FMath::RInterpTo(PawnRotation, FRotator::ZeroRotator, DeltaTime, 5.f);
			SetActorRotation(FRotator(PitchRoll.Pitch, Yaw.Yaw, PitchRoll.Roll));
		}
		else
		{
			SetActorRotation(FRotator(PawnRotation.Pitch, Yaw.Yaw, PawnRotation.Roll));
		}
		
		
	
	}


	if (bShooting)
	{
		ShootClock += DeltaTime;
		if (ShootClock > ShootSpeed)
		{
			Shoot();
			ShootClock = 0.f;
		}
	}
	else
	{
		ShootClock = 1.f;
	}

	

}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCar::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCar::StopShooting);

	PlayerInputComponent->BindAxis("Forward",  this, &APlayerCar::Forward);
	PlayerInputComponent->BindAxis("Right",  this, &APlayerCar::Right);

	// Turn Camera with mouse
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	
}

void APlayerCar::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void APlayerCar::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), Ammo);
	if (Ammo > 0)
	{
		GetWorld()->SpawnActor<ABullet>(BulletBP, GetActorLocation() + GetActorForwardVector() * 100.f + GetActorRightVector() * 100.f, FRotator(0.f, PawnRotation.Yaw, 0.f) - FRotator(0.f, 1.f, 0.f));
		Ammo--;
		if (Ammo > 0)
		{
			GetWorld()->SpawnActor<ABullet>(BulletBP, GetActorLocation() + GetActorForwardVector() * 100.f - GetActorRightVector() * 100.f, FRotator(0.f, PawnRotation.Yaw, 0.f) + FRotator(0.f, 1.f, 0.f));
			Ammo--;
		}
		
	}
	
}

void APlayerCar::StartShooting()
{
	bShooting = true;
}

void APlayerCar::StopShooting()
{
	bShooting = false;
}

void APlayerCar::Forward(float value)
{
	//New for MovementComponent******************************
	FVector RotationVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	FVector Direction = FVector(RotationVector.X, RotationVector.Y, 0.f);



	AddMovementInput(Direction, value);
}

void APlayerCar::Right(float value)
{
	
}



