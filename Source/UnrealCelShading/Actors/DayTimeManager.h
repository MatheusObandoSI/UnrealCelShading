// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialParameterCollection.h"
#include "DayTimeManager.generated.h"

UCLASS()
class UNREALCELSHADING_API ADayTimeManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADayTimeManager();

	UPROPERTY(EditAnywhere)
	ADirectionalLight* DirectionalLight = nullptr;

	UPROPERTY(EditAnywhere)
	float TimeProgressSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* CelShadingParameterCollection = nullptr;

	// UPROPERTY(EditAnywhere)
	// const bool bUseRealTime = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateDayTime(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
