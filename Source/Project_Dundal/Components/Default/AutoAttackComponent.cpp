// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoAttackComponent.h"
#include "Project_Dundal/FighterCharacterBase.h"

// Sets default values for this component's properties
UAutoAttackComponent::UAutoAttackComponent()
{

}


// Called when the game starts
void UAutoAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Start Auto Attack Loop 
void UAutoAttackComponent::StartAutoAttackLoop_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("%s starting auto attack loop"), *GetName()));
	
	GetWorld()->GetTimerManager().SetTimer(AutoAttackTimer, this, &UAutoAttackComponent::AutoAttack_Implementation, AutoAttackInterval, true);
}

// Auto Attack Function Implementation
void UAutoAttackComponent::AutoAttack_Implementation()
{
	if (!EnemyFighter || !IsValid(EnemyFighter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
			FString::Printf(TEXT("%s has no EnemyFighter!"), *GetName()));
		StopAutoAttackLoop();
		return;
	}
    
	if (EnemyFighter->HealthComponent->IsDead())
	{
		StopAutoAttackLoop();
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, 
		FString::Printf(TEXT("%s attacks for %f damage"), *GetName(), AutoAttackDamage));
    
	EnemyFighter->HealthComponent->TakeDamage(AutoAttackDamage);
}

// Stop Auto Attack Loop
void UAutoAttackComponent::StopAutoAttackLoop_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoAttackTimer);
}