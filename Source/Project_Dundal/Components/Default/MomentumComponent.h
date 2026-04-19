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
	UPROPERTY(BlueprintReadWrite)
	float CurrentMomentum = 0.0f;
	UPROPERTY(BlueprintReadWrite)
	float MaxMomentum = 100.0f;
	UPROPERTY(BlueprintReadWrite)
	bool bIsInFlow;
	UPROPERTY(BlueprintReadWrite)
	float FlowDamageMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	EAbilitySlot LastSlot;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterFlow);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_DUNDAL_API UMomentumComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMomentumComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FMomentumData MomentumData;
	
	// Delegate for entering flow state when maximum momentum is gained
	UPROPERTY(BlueprintAssignable)
	FOnEnterFlow OnEnterFlow;
	
	UFUNCTION(BlueprintCallable)
	void AddMomentum();
	
	UFUNCTION(BlueprintCallable)
	void RemoveMomentum();
	
	// Check if momentum is at max, if so activate flow and unlock ultimate for use.
	UFUNCTION(BlueprintCallable)
	void CheckFlow();
	
	// Getters for UI to read Current Momentum and Max Momentum
	UFUNCTION(BlueprintCallable)
	void GetCurrentMomentum();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};