// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "TheBoxData.generated.h"

/**
 * 
 */
class THEBOX_API TheBoxData
{
public:
	TheBoxData();
	~TheBoxData();
};


//// Clues //////////////////////
USTRUCT(BlueprintType)
struct FClues : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Clue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Solution;
};
//// Clues //////////////////////
