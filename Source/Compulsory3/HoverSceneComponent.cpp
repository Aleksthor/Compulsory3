// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverSceneComponent.h"
#include "PlayerCar.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHoverSceneComponent::UHoverSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TraceLength = 200.f;
	HoverForce = 30000.f;
	LinearDamping = 3.f;
	AngularDamping = 5.f;
}


// Called when the game starts
void UHoverSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Player = GetOwner();
	PlayerCar = Cast<APlayerCar>(Player);
}


// Called every frame
void UHoverSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (IsValid(PlayerCar))
	{
		
		FVector WorldLocation = GetComponentLocation();
		FVector UpVector = GetUpVector();
		UpVector *= TraceLength;
		FVector EndLocation = WorldLocation - UpVector;

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, EndLocation, ECC_Visibility, TraceParams);

		if (HitResult.IsValidBlockingHit())
		{
			UE_LOG(LogTemp, Warning, TEXT("Valid Hit"));
			FVector Length = HitResult.Location - WorldLocation;
			float LengthSize = Length.Size();
			float Ratio = LengthSize / TraceLength;

			float Lerp = FMath::Lerp(HoverForce, 0.f, Ratio);

			FVector Force = HitResult.ImpactNormal * Lerp;

			Cast<UPrimitiveComponent>(PlayerCar->GetRootComponent())->AddForceAtLocation(Force, WorldLocation);
			Cast<UPrimitiveComponent>(PlayerCar->GetRootComponent())->SetLinearDamping(LinearDamping);
			Cast<UPrimitiveComponent>(PlayerCar->GetRootComponent())->SetAngularDamping(AngularDamping);
			
			
		}
		
	}

}

