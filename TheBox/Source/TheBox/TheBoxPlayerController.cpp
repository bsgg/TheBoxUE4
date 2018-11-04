// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxPlayerController.h"
#include "TheBoxGameMode.h"

ATheBoxPlayerController::ATheBoxPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATheBoxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Find data
	ATheBoxGameMode* GM = Cast<ATheBoxGameMode>(GetWorld()->GetAuthGameMode());

	if (GM == nullptr) return;

	//FClues clue = GM->GetClueByID(2);

	//UE_LOG(LogTemp, Warning, TEXT("[ATheBoxPlayerController::BeginPlay] Clue %s: %s"), *clue.Clue.ToString(), *clue.Solution.ToString());

}
