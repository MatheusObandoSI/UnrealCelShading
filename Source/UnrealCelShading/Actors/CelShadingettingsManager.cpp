#include "CelShadingSettingsManager.h"
#include "Kismet/KismetMaterialLibrary.h"

ACelShadingSettingsManager::ACelShadingSettingsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACelShadingSettingsManager::SetupCelShadingParameters()
{
	if (IsValid(MaterialParameterCollection))
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("Saturation"), Saturation);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("ShadeContrast"), ShadeContrast);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColorInfluency"), LightColorInfluency);

		if (IsValid(DirectionalLight))
		{
			if (bTrackDirectionalLightColor)
			{
				UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), DirectionalLight->GetLightColor());
			}
			else
			{
				UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), LightColor);
			}

			if (bTrackDirectionalLightIntensity)
			{
				UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), DirectionalLight->GetBrightness() * DirectionalLightIntensityScale);
			}
			else
			{
				UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), LightIntensity);
			}
		}

		else
		{
			UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), LightColor);
			UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), LightIntensity);
		}
	}
}

void ACelShadingSettingsManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupCelShadingParameters();
}

void ACelShadingSettingsManager::BeginPlay()
{
	Super::BeginPlay();

	SetupCelShadingParameters();
	SetActorTickEnabled(bRealTimeLightTracking);
}


void ACelShadingSettingsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(DirectionalLight) && bTrackDirectionalLightColor)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), DirectionalLight->GetLightColor());
	}

	if (IsValid(DirectionalLight) && bTrackDirectionalLightIntensity)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), DirectionalLight->GetBrightness() * DirectionalLightIntensityScale);
	}
}