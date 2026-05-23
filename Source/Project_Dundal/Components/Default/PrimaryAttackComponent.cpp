// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAttackComponent.h"
#include "Project_Dundal/Headers/CombatTypes.h"
#include "Project_Dundal/Components/Default/HealthComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UPrimaryAttackComponent::UPrimaryAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPrimaryAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPrimaryAttackComponent::PunchSweep_Implementation(FAttackStruct AttackData)
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector Forward = GetOwner()->GetActorForwardVector();
	FVector End = Start + (Forward * AttackData.Reach); // Radius = punch reach

	TArray<FHitResult> HitResults;
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(20.f, 15.f, 15.f));
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults, Start, End, 
		GetOwner()->GetActorQuat(),
		ECC_Pawn, Box, Params
	);

	DrawDebugBox(GetWorld(), (Start + End) * 0.5f, Box.GetExtent(), 
		GetOwner()->GetActorQuat(), FColor::Red, false, 1.0f);

	for (FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor) continue;
        
		UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->TakeDamage(AttackData.Damage);
		}
	}
}

void UPrimaryAttackComponent::PerformAttack_Implementation()
{
	if (ComboAttacks.Num() == 0) return;

	FAttackStruct CurrentAttack = ComboAttacks[ComboIndex];
	PunchSweep(CurrentAttack);

	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		ComboTimerHandle, 
		this, 
		&UPrimaryAttackComponent::ResetCombo_Implementation, 
		1.5f, 
		false
	);

	ComboIndex = (ComboIndex + 1) % ComboAttacks.Num();
}

void UPrimaryAttackComponent::ResetCombo_Implementation()
{
	ComboIndex = 0;
}