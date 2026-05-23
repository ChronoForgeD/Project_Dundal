// EnemyCharacterBase.cpp
#include "EnemyCharacterBase.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	AutoAttackComponent = CreateDefaultSubobject<UAutoAttackComponent>(TEXT("AutoAttackComponent"));
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacterBase::PerformEnemyAttack_Implementation()
{
	if (AutoAttackComponent)
	{
		AutoAttackComponent->AutoAttack();
	}
}