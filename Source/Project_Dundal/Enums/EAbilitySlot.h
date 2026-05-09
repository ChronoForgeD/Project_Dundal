#pragma once

#include "CoreMinimal.h"
#include "EAbilitySlot.generated.h"

UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	Engage      UMETA(DisplayName = "Q - Engage"),
	Follow      UMETA(DisplayName = "W - Follow-up"),
	Counter     UMETA(DisplayName = "E - Counter"),
	Interrupt   UMETA(DisplayName = "R - Ultimate"),
	Ultimate    UMETA(DisplayName = "T - Interrupt"),
};