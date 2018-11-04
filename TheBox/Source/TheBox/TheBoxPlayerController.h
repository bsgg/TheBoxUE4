// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheBoxPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ATheBoxPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATheBoxPlayerController();

protected:
	virtual void BeginPlay() override;
};


