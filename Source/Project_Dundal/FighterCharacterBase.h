// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Default/HealthComponent.h"
#include "Components/Default/MomentumComponent.h"
#include "Components/Default/AbilityComponent.h"
#include "GameFramework/Character.h"
#include "FighterCharacterBase.generated.h"

UCLASS()
class PROJECT_DUNDAL_API AFighterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFighterCharacterBase();
	
	// Creating Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMomentumComponent* MomentumComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAbilityComponent* AbilityComponent;

	// Enemy Fighter Tracking
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	AFighterCharacterBase* EnemyFighter;
	
	// Auto Attack Parameters
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float AutoAttackInterval = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float AutoAttackDamage = 5.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Auto Attack Loop
	FTimerHandle AutoAttackTimer;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Start Auto Attack Loop
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void StartAutoAttackLoop();
	
	// Auto Attack Function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AutoAttack();

	// Stop Auto Attack Loop
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void StopAutoAttackLoop();
	
	// Death Handling
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void DeathHandling();
};
