// CombatTypes.h
#pragma once

#include "CoreMinimal.h"
#include "CombatTypes.generated.h"

// Identifies which punch in the combo string is being thrown
// Used by PrimaryAttackComponent to know hit detection direction/shape
UENUM(BlueprintType)
enum class EPunchType : uint8
{
	LeftJab     UMETA(DisplayName = "Left Jab"),
	RightHook   UMETA(DisplayName = "Right Hook"),
	RightJab    UMETA(DisplayName = "Right Jab"),
	LeftHook    UMETA(DisplayName = "Left Hook")
};

// Data container for a single attack in a combo string
// Fill out a TArray of these in the editor to define any combo sequence
USTRUCT(BlueprintType)
struct PROJECT_DUNDAL_API FAttackStruct
{
	GENERATED_BODY()

	// How much damage this hit deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 10.0f;

	// How far the punch reaches (sweep distance from actor center)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Reach = 80.0f;

	// Which punch type this is — drives animation and future hit offset logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	EPunchType PunchType = EPunchType::LeftJab;

	// Animation montage to play for this hit (optional for POC, wire up later)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* Montage = nullptr;
};