// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "FighterCharacterBase.h"
#include "Components/Default/HealthComponent.h"
#include "Components/Default/MomentumComponent.h"
#include "Components/Default/AbilityComponent.h"


// Sets default values
AFighterCharacterBase::AFighterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Component Creation
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MomentumComponent = CreateDefaultSubobject<UMomentumComponent>(TEXT("MomentumComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
}

// Called when the game starts or when spawned
void AFighterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind to Death
	HealthComponent->OnDeath.AddDynamic(this, &AFighterCharacterBase::DeathHandling);
}

// Called to bind functionality to input
void AFighterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Start Auto Attack Loop 
void AFighterCharacterBase::StartAutoAttackLoop_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("%s starting auto attack loop"), *GetName()));
	
	GetWorld()->GetTimerManager().SetTimer(AutoAttackTimer, this, &AFighterCharacterBase::AutoAttack, AutoAttackInterval, true);
}

// Auto Attack Function Implementation
void AFighterCharacterBase::AutoAttack_Implementation()
{
	if (!EnemyFighter)
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
void AFighterCharacterBase::StopAutoAttackLoop_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(AutoAttackTimer);
}

// Death Handling
void AFighterCharacterBase::DeathHandling_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("%s has died!"), *GetName()));
	StopAutoAttackLoop();
}
