// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"

// Sets the default properties for this component's subobjects
UAbilityBase::UAbilityBase()
{
	// Set this ability to be initialized when the game starts
}

void UAbilityBase::ExecuteAbility_Implementation(AActor* Instigator, AActor* Target)
{
	// This is where the logic for executing the ability would go.
	// For example, you could apply damage to the target, play an animation, etc.
	UE_LOG(LogTemp, Warning, TEXT("Executing ability: %s"), *AbilityData.AbilityName.ToString());
	
}

bool UAbilityBase::TryExecuteAbility(AActor* Instigator, AActor* Target)
{
	if (CanExecuteAbility()) return false;
	ExecuteAbility(Instigator, Target);
	StartCooldown();
	OnAbilityExecuted.Broadcast();
	return true;
}

void UAbilityBase::StartCooldown()
{
	if (AbilityData.Cooldown > 0.0f)
	{
		bIsOnCooldown = true;
		CurrentCooldown = AbilityData.Cooldown;
	}
}

bool UAbilityBase::CanExecuteAbility() const
{
	return !bIsOnCooldown;
}

void UAbilityBase::ResetCooldown()
{
	bIsOnCooldown = false;
	CurrentCooldown = 0.0f;
}