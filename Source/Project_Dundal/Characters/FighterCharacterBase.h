// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_Dundal/Components/Default/HealthComponent.h"
#include "Project_Dundal/Components/Default/MomentumComponent.h"
#include "Project_Dundal/Components/Default/AbilityComponent.h"
#include "Project_Dundal/Components/Default/PrimaryAttackComponent.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPrimaryAttackComponent* PrimaryAttackComponent;
	
	// Death Handling
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void DeathHandling();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
