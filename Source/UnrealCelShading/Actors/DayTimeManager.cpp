#include "DayTimeManager.h"


ADayTimeManager::ADayTimeManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADayTimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADayTimeManager::UpdateDayTime(float DeltaTime)
{
	if(IsValid(DirectionalLight))
	{
		DirectionalLight->AddActorLocalRotation(FRotator(0.0f, DeltaTime*TimeProgressSpeed, 0.0f));
	}
}

void ADayTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

