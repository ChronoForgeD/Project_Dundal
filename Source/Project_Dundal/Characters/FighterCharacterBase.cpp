// Fill out your copyright notice in the Description page of Project Settings.

#include "FighterCharacterBase.h"
#include "Engine/Engine.h"
#include "Project_Dundal/Components/Default/HealthComponent.h"
#include "Project_Dundal/Components/Default/MomentumComponent.h"
#include "Project_Dundal/Components/Default/AbilityComponent.h"
#include "Project_Dundal/Components/Default/PrimaryAttackComponent.h"


// Sets default values
AFighterCharacterBase::AFighterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Component Creation
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MomentumComponent = CreateDefaultSubobject<UMomentumComponent>(TEXT("MomentumComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	PrimaryAttackComponent = CreateDefaultSubobject<UPrimaryAttackComponent>(TEXT("PrimaryAttackComponent"));
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

// Death Handling
void AFighterCharacterBase::DeathHandling_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("%s has died!"), *GetName()));
}
