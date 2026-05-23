// EnemyCharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "Project_Dundal/Characters/FighterCharacterBase.h"
#include "Project_Dundal/Components/Default/AutoAttackComponent.h"
#include "EnemyCharacterBase.generated.h"

UCLASS()
class PROJECT_DUNDAL_API AEnemyCharacterBase : public AFighterCharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAutoAttackComponent* AutoAttackComponent;

	// Called by AI controller or behavior tree to trigger an attack
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void PerformEnemyAttack();

protected:
	virtual void BeginPlay() override;
};