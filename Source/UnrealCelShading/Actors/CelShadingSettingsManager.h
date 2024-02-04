#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Materials/MaterialParameterCollection.h"
#include "CelShadingSettingsManager.generated.h"

UCLASS()
class UNREALCELSHADING_API ACelShadingSettingsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACelShadingSettingsManager();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* SourceLight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialParameterCollection* MaterialParameterCollection = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
    float Saturation = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTrackSourceLightIntensity = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
    float LightIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
    float LightIntensityScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
    float ShadeContrast = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTrackSourceLightColor = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor LightColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float LightColorInfluency = 0.5f;


protected:
    virtual void BeginPlay() override;

    virtual void OnConstruction(const FTransform& Transform) override;

private:
    virtual void SetupCelShadingParameters();
};
