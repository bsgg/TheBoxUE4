// Fill out your copyright notice in the Description page of Project Settings.

#include "PasswordBoard.h"
#include "Components/TextRenderComponent.h"
#include "Button3D.h"

// Sets default values
APasswordBoard::APasswordBoard()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;


	PasswordText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Password"));
	PasswordText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	PasswordText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));


	IndexCharacterPassword = 0;
	ABCArray = { "0", "1", "2", "3","4","5","6","7","8","9", "A",  "B",  "C",  "D",  "E",  "G",  "H", "I", "J", "K", "L", "M", "O", "P", "Q", "R", "S", "T", "U", "V", "W",  "X",  "Y", "Z" };


	FText abc = FText::FromString(ABCArray[IndexCharacterPassword]);
	PasswordText->SetText(abc);

	PasswordText->SetupAttachment(DummyRoot);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APasswordBoard::BeginPlay()
{
	Super::BeginPlay();

	if (Button3DClass == nullptr) return;

	FActorSpawnParameters spawnParamenters;
	spawnParamenters.Owner = this;
	spawnParamenters.Instigator = Instigator;

	IncreaseButton = GetWorld()->SpawnActor<AButton3D>(Button3DClass, GetActorLocation(), FRotator::ZeroRotator, spawnParamenters);

	if (IncreaseButton != nullptr)
	{
		IncreaseButton->SetActorLabel("IncreaseButton");
	}


	DecreaseButton = GetWorld()->SpawnActor<AButton3D>(Button3DClass, GetActorLocation(), FRotator::ZeroRotator, spawnParamenters);

	if (DecreaseButton != nullptr)
	{
		DecreaseButton->SetActorLabel("DecreaseButton");
	}

}

void APasswordBoard::UpdateCharacterPassword(int32 direction)
{

}


// Called every frame
void APasswordBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

