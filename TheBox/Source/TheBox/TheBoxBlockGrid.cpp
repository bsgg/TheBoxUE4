// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TheBoxBlockGrid.h"
#include "TheBoxBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATheBoxBlockGrid::ATheBoxBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));

	IndexABC = 0;
	ABCArray = { "0", "1", "2", "3","4","5","6","7","8","9", "A",  "B",  "C",  "D",  "E",  "G",  "H", "I", "J", "K", "L", "M", "O", "P", "Q", "R", "S", "T", "U", "V", "W",  "X",  "Y", "Z" };


	FText abc = FText::FromString(ABCArray[IndexABC]);
	ScoreText->SetText(abc);

	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ATheBoxBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ATheBoxBlock* NewBlock = GetWorld()->SpawnActor<ATheBoxBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}


void ATheBoxBlockGrid::AdvancedABC()
{
	IndexABC++;

	if (IndexABC >= ABCArray.Num())
	{
		IndexABC = ABCArray.Num() - 1;
	}

	FText abc = FText::FromString(ABCArray[IndexABC]);
	ScoreText->SetText(abc);	

}

void ATheBoxBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
