#include "ActorRotationComponent.h"


UActorRotationComponent::UActorRotationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}
void UActorRotationComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<AActor>(GetOwner());
}

void UActorRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FRotator Rotation = FRotator(RotationAxis.X, RotationAxis.Y, RotationAxis.Z);

    if (IsValid(Owner))
    {
        Owner->AddActorLocalRotation(Rotation);
    }
}