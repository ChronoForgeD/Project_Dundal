// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_Dundal/Enums/EAbilitySlot.h"
#include "AbilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitySlotExecuted, EAbilitySlot, Slot);

class UAbilityBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class PROJECT_DUNDAL_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();
	
	// Delegate for when ability fires
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnAbilitySlotExecuted OnAbilitySlotExecuted;
	
	// Loadout Map
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	TMap<EAbilitySlot, UAbilityBase*> Loadout;
	
	// Assign an ability to a slot
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AssignAbility(EAbilitySlot Slot, UAbilityBase* Ability);
	
	// Tick override for cooldown
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Getter for UI
	UFUNCTION(BlueprintPure, Category = "Abilities")
	UAbilityBase* GetAbilityInSlot(EAbilitySlot Slot) const;
	
	// Call TryExecute
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ExecuteSlot(EAbilitySlot Slot, AActor* Target);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
