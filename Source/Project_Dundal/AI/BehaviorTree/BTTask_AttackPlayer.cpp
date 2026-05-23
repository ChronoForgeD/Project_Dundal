// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"
#include "Project_Dundal/FighterCharacterBase.h"
#include "AIController.h"
#include "Project_Dundal/Components/Default/HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Constructor

UBTTask_AttackPlayer::UBTTask_AttackPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Attack Player");
}

// Execute Task
EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the controlled pawn (enemy character)
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed; // No pawn to control
	}

	// Cast to the specific enemy type
	AFighterCharacterBase* EnemyCharacter = Cast<AFighterCharacterBase>(ControlledPawn);
	if (!EnemyCharacter)
	{
		return EBTNodeResult::Failed; // Not the expected enemy type
	}
	
	// Check if target player is dead
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp)
	{
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("Player"));
		if (TargetActor)
		{
			UHealthComponent* TargetHealth = TargetActor->FindComponentByClass<UHealthComponent>();
			if (TargetHealth && TargetHealth->IsDead())
			{
				return EBTNodeResult::Failed;
			}
		}
	}

	// Call the attack function on the enemy character
	EnemyCharacter->PrimaryAttackComponent->PerformAttack();

	return EBTNodeResult::Succeeded; // Task completed successfully
}