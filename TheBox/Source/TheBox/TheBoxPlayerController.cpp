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

	

}
