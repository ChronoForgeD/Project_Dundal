// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_Dundal/Enums/EAbilitySlot.h"
#include "Components/ActorComponent.h"
#include "MomentumComponent.generated.h"

// Struct for Momentum/Flow Data
USTRUCT(BlueprintType)
struct FMomentumData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	float MaxMomentum = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float FlowDamageMultiplier = 1.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterFlow);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitFlow);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_DUNDAL_API UMomentumComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMomentumComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FMomentumData MomentumData;
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentMomentum = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
	EAbilitySlot LastSlot = EAbilitySlot::Engage;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsInFlow = false;
	
	// Delegate for entering state when maximum momentum is gained and exiting flow when meter is depleted
	UPROPERTY(BlueprintAssignable)
	FOnEnterFlow OnEnterFlow;
	
	UPROPERTY(BlueprintAssignable)
	FOnExitFlow OnExitFlow;
	
	UFUNCTION(BlueprintCallable)
	void AddMomentum(float Amount, EAbilitySlot Slot);
	
	UFUNCTION(BlueprintCallable)
	void RemoveMomentum(float Amount);
	
	// Getters for UI to read Current Momentum and Max Momentum
	UFUNCTION(BlueprintPure)
	float GetMomentumPercentage() const;
	
	// Exit flow when ultimate is used
	UFUNCTION(BlueprintCallable)
	void ExitFlow();
	
	// Check if ultimate is ready
	UFUNCTION(BlueprintPure)
	bool IsUltimateReady() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Check if momentum is at max, if so activate flow and unlock ultimate for use.
	UFUNCTION()
	void CheckFlow();
};