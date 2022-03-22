// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); // Inherited from UAnimInstance
	}


}

void UEnemyAnimInstance::UpdateAnimationProperties()
{
	
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner(); // Inherited from UAnimInstance
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
	
}
