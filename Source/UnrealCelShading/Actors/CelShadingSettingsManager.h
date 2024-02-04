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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Saturation = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTrackSourceLightIntensity = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightIntensityScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShadeContrast = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTrackSourceLightColor = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor LightColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightColorInfluency = 0.5f;


protected:

    virtual void BeginPlay() override;

    virtual void OnConstruction(const FTransform& Transform) override;
};
