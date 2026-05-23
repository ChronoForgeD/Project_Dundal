// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_Dundal/Headers/CombatTypes.h"
#include "PrimaryAttackComponent.generated.h"

class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_DUNDAL_API UPrimaryAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPrimaryAttackComponent();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	TArray<FAttackStruct> ComboAttacks;

	int32 ComboIndex = 0;
	FTimerHandle ComboTimerHandle;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
	void PerformAttack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
	void ResetCombo();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
	void PunchSweep(FAttackStruct AttackData);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
