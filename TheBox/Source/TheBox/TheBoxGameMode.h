// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheBoxData.h"

#include "TheBoxGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATheBoxGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheBoxGameMode();

	UFUNCTION(BlueprintCallable)
	FClues GetClueByID(int32 id) const;

protected:

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* CluesDB; // Clues database database

	class UFileDownloader* FileDownloader;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDownloadEnd(const EDownloadResult Result);
};



