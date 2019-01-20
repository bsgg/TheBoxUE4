// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Button3D.generated.h"

UCLASS()
class THEBOX_API AButton3D : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ButtonMesh;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UMaterialInstance* HighlightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UMaterialInterface* UnHighlighMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float TotalHightlighButtonTime = 0.1f;
	
public:	
	AButton3D();

	void BeginPlay();

	void Tick(float DeltaTime);

	UFUNCTION()
	void ButtonClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void OnFingerPressedButton(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);	

public:	

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }


	FORCEINLINE class UStaticMeshComponent* GetButtonMesh() const { return ButtonMesh; }

private:

	void HandleClicked();

	void Hightlight();

	void UnHighligh();

private:

	bool bClicked;

	float CurrentHightlighTime = 0.0f;
	

};
