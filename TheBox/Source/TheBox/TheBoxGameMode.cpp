// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxGameMode.h"
#include "TheBoxPlayerController.h"
#include "TheBoxPawn.h"
#include "FileDownloader.h"

ATheBoxGameMode::ATheBoxGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATheBoxPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATheBoxPlayerController::StaticClass();

}

void ATheBoxGameMode::BeginPlay()
{
	Super::BeginPlay();

	FileDownloader = UFileDownloader::MakeDownloader();

	if (FileDownloader != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::ATheBoxGameMode FileDownloader not null"));
		FileDownloader->OnResult.AddDynamic(this, &ATheBoxGameMode::OnDownloadEnd);

		const FString url = "http://beatrizcv.com/Data/TreasureHunter/TreasureHunterData.json";
		FString savePath = "D://Downloads//TestDownloads//TreasureHunterData.json";
		FileDownloader->DownloadFile(url, savePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::ATheBoxGameMode FileDownloader  NULL"));
	}
	

}

void ATheBoxGameMode::OnDownloadEnd(const EDownloadResult Result)
{
	switch (Result)
	{
		case EDownloadResult::Success:
			UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::OnDownloadEnd EDownloadResult::Success"));
		break;
		case EDownloadResult::SaveFailed:
			UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::OnDownloadEnd EDownloadResult::SaveFailed"));
			break;
		case EDownloadResult::DownloadFailed:
			UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::OnDownloadEnd EDownloadResult::DownloadFailed"));
			break;
		case EDownloadResult::DirectoryCreationFailed:
			UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::OnDownloadEnd EDownloadResult::DirectoryCreationFailed"));
			break;
	}

	
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
