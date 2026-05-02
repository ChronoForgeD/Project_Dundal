// Fill out your copyright notice in the Description page of Project Settings.


#include "MomentumComponent.h"

// Sets default values for this component's properties
UMomentumComponent::UMomentumComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void UMomentumComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UMomentumComponent::AddMomentum(float Amount, EAbilitySlot Slot)
{
	CurrentMomentum = FMath::Clamp(CurrentMomentum + Amount, 0.0f, MomentumData.MaxMomentum);
	LastSlot = Slot;
	CheckFlow();
}

void UMomentumComponent::RemoveMomentum(float Amount)
{
	CurrentMomentum = FMath::Clamp(CurrentMomentum - Amount, 0.0f, MomentumData.MaxMomentum);
	CheckFlow();
}

void UMomentumComponent::CheckFlow()
{
	if (!bIsInFlow && CurrentMomentum >= MomentumData.MaxMomentum)
	{
		bIsInFlow = true;
		OnEnterFlow.Broadcast();
	}
	else if (bIsInFlow && CurrentMomentum <= 0.0f)
	{
		bIsInFlow = false;
		OnExitFlow.Broadcast();
	}
}

float UMomentumComponent::GetMomentumPercentage() const
{
	if (MomentumData.MaxMomentum <= 0) return 0.0f;
	return CurrentMomentum / MomentumData.MaxMomentum;
}

void UMomentumComponent::ExitFlow()
{
	CurrentMomentum = 0.0f;
	CheckFlow();
}

bool UMomentumComponent::IsUltimateReady() const
{
	return bIsInFlow;
}