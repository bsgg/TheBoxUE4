// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheBoxData.h"
#include "TheBoxGameMode.generated.h"

// Delegate DataLoaded
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDataLoaded);

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATheBoxGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheBoxGameMode(); 

	// Declaring a variable to store the delegate:
	UPROPERTY(BlueprintAssignable, Category = "Data")
	FDataLoaded OnDataLoaded;

	UFUNCTION(BlueprintImplementableEvent, Category = "Data")
	void OnDataLoadedEvent();

	UFUNCTION(BlueprintCallable, Category = "Data")
	FClues GetClueByID(int32 id) const;

	UFUNCTION(BlueprintCallable, Category = "Data")
	FClues GetCurrentClue() const;

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

	int32 ClueIndex;

	class UFileDownloader* FileDownloader;
	FString CluesLocalSavePath;

	UFUNCTION()
	void OnDownloadEnd(const EDownloadResult Result);

};



