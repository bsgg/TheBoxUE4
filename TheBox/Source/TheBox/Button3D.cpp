// Fill out your copyright notice in the Description page of Project Settings.

#include "Button3D.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AButton3D::AButton3D()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));
	RootComponent = DummyRoot;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(DummyRoot);


	ButtonMesh->OnClicked.AddDynamic(this, &AButton3D::ButtonClicked);
	ButtonMesh->OnInputTouchBegin.AddDynamic(this, &AButton3D::OnFingerPressedButton);

	bClicked = false;

	PrimaryActorTick.bCanEverTick = true;
}

void AButton3D::BeginPlay()
{
	Super::BeginPlay();

	UnHighligh();

}

void AButton3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bClicked) return;
	
	if (CurrentHightlighTime < TotalHightlighButtonTime)
	{
		CurrentHightlighTime += DeltaTime;
	}
	else
	{
		CurrentHightlighTime = 0.0f;
		UnHighligh();
		bClicked = false;
	}

}

void AButton3D::Hightlight()
{
	if (HighlightMaterial == nullptr) return;

	ButtonMesh->SetMaterial(0, HighlightMaterial);
}

void AButton3D::UnHighligh()
{
	if (UnHighlighMaterial == nullptr) return;

	ButtonMesh->SetMaterial(0, UnHighlighMaterial);
}

void AButton3D::ButtonClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void AButton3D::OnFingerPressedButton(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AButton3D::HandleClicked()
{

	if (bClicked) return;

	UE_LOG(LogTemp, Warning, TEXT("[AButton3D::HandleClicked]"));

	CurrentHightlighTime = 0.0f;

	Hightlight();

	bClicked = true;
}


