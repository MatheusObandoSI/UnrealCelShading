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
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), LightIntensity * LightIntensityScale);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColorInfluency"), LightColorInfluency);

		if (IsValid(SourceLight))
		{
			if (bTrackSourceLightColor)
			{
				UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), SourceLight->GetLightColor());
			}
			else
			{
				UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), LightColor);
			}
		}

		else
		{
			UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), LightColor);
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
}


void ACelShadingSettingsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(SourceLight) && bTrackSourceLightColor)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, FName("LightColor"), SourceLight->GetLightColor());
	}

	if (IsValid(SourceLight) && bTrackSourceLightIntensity)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("LightIntensity"), SourceLight->GetBrightness() * LightIntensityScale);
	}
}