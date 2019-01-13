// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class THEBOX_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetText(FText Text);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCharacterText(FText Text);

protected:
	virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessagesTxt;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ABCTxt;
	
};
