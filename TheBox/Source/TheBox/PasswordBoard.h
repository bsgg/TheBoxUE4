// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PasswordBoard.generated.h"

UCLASS()
class THEBOX_API APasswordBoard : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = "Pawssword Board", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = "Pawssword Board", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* PasswordText;


	UPROPERTY(EditDefaultsOnly, Category = "Pawssword Board")
	TSubclassOf<class AButton3D> Button3DClass;

	class AButton3D* IncreaseButton;
	
	class AButton3D* DecreaseButton;


	int32 IndexCharacterPassword;
	TArray<FString> ABCArray;
	
public:	
	// Sets default values for this actor's properties
	APasswordBoard();

	void UpdateCharacterPassword(int32 direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

	FORCEINLINE class UTextRenderComponent* GetPasswordText() const { return PasswordText; }

};
