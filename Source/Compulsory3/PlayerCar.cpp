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
#include "HoverSceneComponent.h"



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
	
	HoverComponent1 = CreateDefaultSubobject<UHoverSceneComponent>(TEXT("HoverComponent1"));
	HoverComponent1->SetupAttachment(Collider);
	HoverComponent1->SetRelativeLocation(FVector(60.f, 60.f, 0.f));

	HoverComponent2 = CreateDefaultSubobject<UHoverSceneComponent>(TEXT("HoverComponent2"));
	HoverComponent2->SetupAttachment(Collider);
	HoverComponent2->SetRelativeLocation(FVector(60.f, -60.f, 0.f));

	HoverComponent3 = CreateDefaultSubobject<UHoverSceneComponent>(TEXT("HoverComponent3"));
	HoverComponent3->SetupAttachment(Collider);
	HoverComponent3->SetRelativeLocation(FVector(-60.f, 60.f, 0.f));

	HoverComponent4 = CreateDefaultSubobject<UHoverSceneComponent>(TEXT("HoverComponent4"));
	HoverComponent4->SetupAttachment(Collider);
	HoverComponent4->SetRelativeLocation(FVector(-60.f, -60.f, 0.f));

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
		FRotator UseRotator = PawnRotation;

		FVector ImpactPoints1 = HoverComponent1->HitResult.ImpactPoint;
		FVector ImpactPoints2 = HoverComponent2->HitResult.ImpactPoint;
		FVector ImpactPoints3 = HoverComponent3->HitResult.ImpactPoint;
		FVector ImpactPoints4 = HoverComponent4->HitResult.ImpactPoint;
		if (ImpactPoints1.IsNearlyZero() && ImpactPoints2.IsNearlyZero() && ImpactPoints3.IsNearlyZero() && ImpactPoints4.IsNearlyZero())
		{
			UseRotator = FMath::RInterpTo(PawnRotation, FRotator::ZeroRotator, DeltaTime, 5.f);
			
			UE_LOG(LogTemp, Warning, TEXT("HoverComponent In Air"));
			HoverComponent1->LinearDamping = 1.f;
			HoverComponent2->LinearDamping = 1.f;
			HoverComponent3->LinearDamping = 1.f;
			HoverComponent4->LinearDamping = 1.f;

			HoverComponent1->AngularDamping = 1.f;
			HoverComponent2->AngularDamping = 1.f;
			HoverComponent3->AngularDamping = 1.f;
			HoverComponent4->AngularDamping = 1.f;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HoverComponent Default"));
			HoverComponent1->LinearDamping = HoverComponent1->LinearDampingDefault;
			HoverComponent2->LinearDamping = HoverComponent2->LinearDampingDefault;
			HoverComponent3->LinearDamping = HoverComponent3->LinearDampingDefault;
			HoverComponent4->LinearDamping = HoverComponent4->LinearDampingDefault;

			HoverComponent1->AngularDamping = HoverComponent1->AngularDampingDefault;
			HoverComponent2->AngularDamping = HoverComponent2->AngularDampingDefault;
			HoverComponent3->AngularDamping = HoverComponent3->AngularDampingDefault;
			HoverComponent4->AngularDamping = HoverComponent4->AngularDampingDefault;
		}
		SetActorRotation(FRotator(UseRotator.Pitch, Yaw.Yaw, UseRotator.Roll));
		
		
		
	
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
	
	FVector RotationVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	FVector ZRotation = PawnRotation.Vector();
	/*FVector Difference = RotationVector - ZRotation;*/
	FVector Direction = FVector(RotationVector.X, RotationVector.Y, ZRotation.Z);
	/*float TurnRate{ 0.01f };
	FVector Direction = FVector(ZRotation.X + FMath::Clamp(Difference.X, -TurnRate, TurnRate),
		ZRotation.Y + FMath::Clamp(Difference.Y, -TurnRate, TurnRate), ZRotation.Z);
	Direction.Normalize();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Direction.ToString());*/


	AddMovementInput(Direction, value);
}

void APlayerCar::Right(float value)
{
	
}



