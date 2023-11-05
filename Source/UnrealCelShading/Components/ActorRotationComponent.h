#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorRotationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALCELSHADING_API UActorRotationComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UActorRotationComponent();

    UPROPERTY(EditAnywhere, Category = "Rotation")
    FVector RotationAxis = FVector(0.0f, 50.0f, 0.0f);

protected:

    virtual void BeginPlay() override;

private:

    AActor* Owner = nullptr;

public:

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};