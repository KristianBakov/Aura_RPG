// Copyright Kristian Bakov 2024

#pragma once
#define MAX_ARMOR_PENETRATION 100.0f
#define MAX_ARMOR 100.0f
#define ARMOR_PENETRATION_CURVE_NAME "ArmorPenetration"
#define EFFECTIVE_ARMOR_CURVE_NAME "EffectiveArmor"

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
