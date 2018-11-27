// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameUI.h"
#include "Components/TextBlock.h"

bool UInGameUI::Initialize()
{
	bool sucess = Super::Initialize();

	if (!sucess) return false;

	return true;
}

void UInGameUI::SetText(FText Text)
{
	MessagesTxt->SetText(Text);
}