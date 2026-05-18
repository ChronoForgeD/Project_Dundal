// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "Project_Dundal/Abilities/AbilityBase.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// GetAbilityInSlot
UAbilityBase* UAbilityComponent::GetAbilityInSlot(EAbilitySlot Slot) const
{
	if (UAbilityBase* const* Found = Loadout.Find(Slot))
	{
		return *Found;
	}
	return nullptr;
}

// ExecuteSlot
void UAbilityComponent::ExecuteSlot(EAbilitySlot Slot, AActor* Target)
{
	if (UAbilityBase** Found = Loadout.Find(Slot))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, 
		   FString::Printf(TEXT("Found ability in slot, calling TryExecute")));
		
		if ((*Found)->TryExecuteAbility(GetOwner(), Target))
		{
			OnAbilitySlotExecuted.Broadcast(Slot);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		   FString::Printf(TEXT("No ability in slot %d") , (int)Slot));
	}
}

// Tick Cooldown iteration
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Iterate through abilities and tick cooldowns
	for (auto& Elem : Loadout)
	{
		if (Elem.Value && Elem.Value->bIsOnCooldown)
		{
			Elem.Value->CurrentCooldown -= DeltaTime;
			if (Elem.Value->CurrentCooldown <= 0.0f)
			{
				Elem.Value->ResetCooldown();
			}
		}
	}
}
// AssignAbilityToSlot
void UAbilityComponent::AssignAbility(EAbilitySlot Slot, UAbilityBase* Ability)
{
	if (Ability)
	{
		Loadout.Add(Slot, Ability);
	}
}