// Copyright Epic Games, Inc. All Rights Reserved.


#include "Compulsory3GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ACompulsory3GameModeBase::ACompulsory3GameModeBase()
{

}

void ACompulsory3GameModeBase::LoadMap1()
{
	FName Level1 = FName("Map");
	UGameplayStatics::OpenLevel(GetWorld(), Level1);
}

void ACompulsory3GameModeBase::LoadMap2()
{
	FName Level1 = FName("Map2");
	UGameplayStatics::OpenLevel(GetWorld(), Level1);
}
