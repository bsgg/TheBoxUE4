// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxGameMode.h"
#include "TheBoxPlayerController.h"
#include "TheBoxPawn.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
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

		//http://beatrizcv.com/Data/TheBox
		//D://Downloads//TestDownloads
		// TheBoxClues.csv

		FString dataFolder = "Data";
		FString cluesServerUrl = FPaths::Combine(DataServerUrl, CluesFileName);
		CluesLocalSavePath = FPaths::Combine(FPaths::ProjectContentDir(), dataFolder, CluesFileName);

		FString gamecontent = FPaths::ProjectContentDir();

		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::ATheBoxGameMode GameContentDir %s "), *gamecontent);

		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::ATheBoxGameMode Trying to download %s on %s"), *cluesServerUrl, *CluesLocalSavePath);

		FileDownloader->DownloadFile(cluesServerUrl, CluesLocalSavePath);
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
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] EDownloadResult::Success"));

			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] The file was saved  on %s"), *CluesLocalSavePath);
		break;
		case EDownloadResult::SaveFailed:
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] EDownloadResult::SaveFailed"));
			break;
		case EDownloadResult::DownloadFailed:
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] EDownloadResult::DownloadFailed"));
			break;
		case EDownloadResult::DirectoryCreationFailed:
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] EDownloadResult::DirectoryCreationFailed"));
			break;
	}

	
	if (Result != EDownloadResult::Success)
	{
		return;
	}
	if (!FPaths::FileExists(CluesLocalSavePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] File %s doesn't exist"), *CluesLocalSavePath);

		return;
	}

	FString FileContent;
	//Read the csv file
	bool fileLoaded = FFileHelper::LoadFileToString(FileContent, *CluesLocalSavePath);


	if (!fileLoaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] Unable to read %s"), *CluesLocalSavePath);

		return;

	}

	TArray<FString> errors = CluesDB->CreateTableFromCSVString(FileContent);

	if (errors.Num() > 0)
	{
		for (int32 errorIdx = 0; errorIdx < errors.Num(); errorIdx++)
		{
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] Error %i/%i = %s"), errorIdx, errors.Num(), *errors[errorIdx]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATheBoxGameMode::OnDownloadEnd No errors found"));
		/*FName rowName = FName(*FString::FromInt(3));
		FClues* row = CluesDB->FindRow<FClues>(rowName, FString(""), true);
		if (row != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] Trying to find row %s =  %s"), *row->Clue.ToString(), *row->Solution.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::OnDownloadEnd] Row %s not found"), *rowName.ToString());
		}*/

		OnDataLoadedEvent();
	}
	
}

FClues ATheBoxGameMode::GetClueByID(int32 id) const
{
	FClues result;
	result.Clue = FText::GetEmpty();
	result.Solution = FText::GetEmpty();

	if (CluesDB == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] CluesDB doesn't exist"));
		return result;
	}

	int32 nClues = CluesDB->RowMap.Num();

	UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] Number Clues: %i"), nClues);
	
	if ((id < 0) || (id >= nClues))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATheBoxGameMode::GetObjectByID] id %i out of range"), id);

		return result;
	}


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
