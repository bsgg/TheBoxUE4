// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxGameMode.h"
#include "TheBoxPlayerController.h"
#include "TheBoxPawn.h"

ATheBoxGameMode::ATheBoxGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATheBoxPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATheBoxPlayerController::StaticClass();
}



FClues ATheBoxGameMode::GetClueByID(int32 id) const
{
	FClues result;

	if (CluesDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::GetObjectByID ObjectDB doesn't exist"));
		return result;
	}

	int32 nClues = CluesDB->RowMap.Num();

	UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] Number Clues: %i"), nClues);
	
	if ((id < 0) || (id >= nClues))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] id %i out of range"), id);

		return result;
	}

	//CluesDB->RowMap[]
	FName rowName = FName(*FString::FromInt(id));

	UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] Trying to find row %s"), *rowName.ToString());

	FClues* row = CluesDB->FindRow<FClues>(rowName, FString(""), true);

	if (row == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] The row %i null"), id);
	}
	else
	{
		result.Clue = row->Clue;
		result.Solution = row->Solution;
	}

	return (result);
}
