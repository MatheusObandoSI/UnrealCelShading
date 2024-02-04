#pragma once

#include "CoreMinimal.h"
#include "Components/DirectionalLightComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Materials/MaterialParameterCollection.h"
#include "DayTimeManager.generated.h"

UCLASS()
class UNREALCELSHADING_API ADayTimeManager : public AActor
{
	GENERATED_BODY()

public:

    ADayTimeManager();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* SunLight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialParameterCollection* MaterialParameterCollection = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialDayProgress = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DayDuration = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinShadeContrast = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxShadeContrast = 1.0f;

protected:

    virtual void BeginPlay() override;

private:

    void UpdateSunPosition(float DeltaTime);
    void UpdateShadeContrast();

    float DayProgress = 0.0f;
    FRotator InitialSunRotation;
};
