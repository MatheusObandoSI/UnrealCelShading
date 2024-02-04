#include "DayTimeManager.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TimerManager.h"

ADayTimeManager::ADayTimeManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADayTimeManager::BeginPlay()
{
    Super::BeginPlay();

    InitialSunRotation = SunLight ? SunLight->GetActorRotation() : FRotator::ZeroRotator;
}

void ADayTimeManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //const float TimeProgress = fmod(GetWorld()->GetTimeSeconds(), DayDuration * 60.0f) / (DayDuration * 60.0f);
    DayProgress = fmod(GetWorld()->GetTimeSeconds(), DayDuration * 60.0f) / (DayDuration * 60.0f);
    /*DayProgress = fmod(GetWorld()->GetTimeSeconds(), DayDuration * 60.0f) / (DayDuration * 60.0f);*/
    UpdateSunPosition(DeltaTime);
    UpdateShadeContrast();
}

void ADayTimeManager::UpdateSunPosition(float DeltaTime)
{
    if (!IsValid(SunLight))
        return;

    const float StartAngle = FMath::Fmod(540.0f * InitialDayProgress, 360.0f);
    const float TotalRotationDegrees = FMath::Fmod((360.0f * DayProgress) + StartAngle, 360.0f);

    const FQuat PitchRotation = FQuat(FVector::RightVector, FMath::DegreesToRadians(TotalRotationDegrees));
    const FQuat InitialYawRotation = FQuat(FVector::UpVector, FMath::DegreesToRadians(InitialSunRotation.Yaw));
    const FQuat InitialRollRotation = FQuat(FVector::ForwardVector, FMath::DegreesToRadians(InitialSunRotation.Roll));

    const FQuat CombinedRotation = InitialYawRotation * InitialRollRotation * PitchRotation;
    SunLight->SetActorRotation(CombinedRotation.Rotator());
}

void ADayTimeManager::UpdateShadeContrast()
{
    if (!IsValid(MaterialParameterCollection)) 
        return;

    /*const float ContrastValue = FMath::Lerp(MinShadeContrast, MaxShadeContrast, DayProgress);*/
    float SinusoidalProgress = sin(fmod(DayProgress + InitialDayProgress, 1.0f) * PI);
    float NormalizedProgress = (SinusoidalProgress + 1.0f) / 2.0f;
    float ContrastValue = FMath::Lerp(MinShadeContrast, MaxShadeContrast, NormalizedProgress);

    UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MaterialParameterCollection, FName("ShadeContrast"), ContrastValue);
}