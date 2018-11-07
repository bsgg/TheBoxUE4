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

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class UDataTable* CluesDB; 

	UPROPERTY(EditDefaultsOnly, Category = "Data Settings")
	FString DataServerUrl;  

	UPROPERTY(EditDefaultsOnly, Category = "Data Settings")
	FString LocalDownloadPath;

	UPROPERTY(EditDefaultsOnly, Category = "Data Settings")
	FString CluesFileName;

protected:
	virtual void BeginPlay() override;

private:

	class UFileDownloader* FileDownloader;
	FString CluesLocalSavePath;

	UPROPERTY(EditDefaultsOnly, Category = "Data Settings")
	class UDataTable* LocalCluesDB; 

	UFUNCTION()
	void OnDownloadEnd(const EDownloadResult Result);
};



