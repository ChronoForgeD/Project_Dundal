// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AutoAttackComponent.generated.h"

class AFighterCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_DUNDAL_API UAutoAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAutoAttackComponent();

	// Auto Attack Parameters
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float AutoAttackInterval = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float AutoAttackDamage = 5.0f;
	
	// Start Auto Attack Loop
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void StartAutoAttackLoop();
	
	// Auto Attack Function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AutoAttack();

	// Stop Auto Attack Loop
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void StopAutoAttackLoop();
	
	// Enemy Fighter Tracking
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	AFighterCharacterBase* EnemyFighter;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Auto Attack Loop
	FTimerHandle AutoAttackTimer;
};
