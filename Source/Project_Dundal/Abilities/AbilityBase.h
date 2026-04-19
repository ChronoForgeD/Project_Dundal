// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/NoExportTypes.h"
#include "Project_Dundal/Enums/EAbilitySlot.h"
#include "AbilityBase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FText AbilityName;
	UPROPERTY(BlueprintReadWrite)
	float Damage = 10.0f;
	UPROPERTY(BlueprintReadWrite)
	float Cooldown = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float StartupTime = 0.1f;
	UPROPERTY(BlueprintReadWrite)
	EAbilitySlot Slot = EAbilitySlot::Engage;
	UPROPERTY(BlueprintReadWrite)
	UAnimMontage* AnimationMontage = nullptr;
};

class UAbilityBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityExecuted);

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class PROJECT_DUNDAL_API UAbilityBase : public UObject
{
	GENERATED_BODY()
	
	public:
	
	UAbilityBase();
	
	// Struct data variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FAbilityData AbilityData;
	
	// Runtime State
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bIsOnCooldown;
	
	// Delegates and Functions 
	UPROPERTY(BlueprintAssignable)
	FOnAbilityExecuted OnAbilityExecuted;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Ability")
	void ExecuteAbility(AActor* Instigator, AActor* Target);
};
