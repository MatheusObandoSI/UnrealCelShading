#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorLocationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCELSHADING_API UActorLocationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorLocationComponent();

	UPROPERTY(EditAnywhere, Category = "Displacement")
	FVector StartLocation = FVector(0.0f, 0.0, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Displacement")
	FVector EndLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Displacement")
	float MovementSpeed = 20.0f;

protected:
	virtual void BeginPlay() override;

	void UpdateActorMovement(float DeltaTime);

private:
	AActor* Owner = nullptr;

	UPROPERTY(meta=(ClampMin = 0.0f, ClampMax = 1.0f))
	float Progress = 0.0f;

	FVector OriginalLocation = FVector();

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
