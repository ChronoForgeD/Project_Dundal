#pragma once

#include "CoreMinimal.h"
#include "EAbilitySlot.generated.h"

UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	Engage      UMETA(DisplayName = "E - Engage"),
	Follow      UMETA(DisplayName = "Q - Follow-up"),
	Counter     UMETA(DisplayName = "W - Counter"),
	Interrupt   UMETA(DisplayName = "Interrupt"),
	Ultimate    UMETA(DisplayName = "Ultimate"),
};