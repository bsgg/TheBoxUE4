// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxPlayerController.h"

ATheBoxPlayerController::ATheBoxPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
