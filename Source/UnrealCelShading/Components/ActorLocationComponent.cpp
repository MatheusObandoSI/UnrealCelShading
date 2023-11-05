#include "ActorLocationComponent.h"
#include "Math/UnrealMathUtility.h"

#include "FrameTypes.h"

UActorLocationComponent::UActorLocationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorLocationComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AActor>(GetOwner());
	OriginalLocation = Owner->GetActorLocation();
}

void UActorLocationComponent::UpdateActorMovement(float DeltaTime)
{
	Progress += DeltaTime * MovementSpeed;
	const FVector& CurrentLocation =  FMath::Lerp<FVector>(StartLocation, EndLocation, Progress);
	Owner->SetActorRelativeLocation(OriginalLocation + CurrentLocation);
	if(Progress >= 1.0f || Progress <= 0.0f)
	{
		MovementSpeed = -MovementSpeed;
	}
}

void UActorLocationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(Owner))
	{
		UpdateActorMovement(DeltaTime);
	}
}

