// Copyright Kristian Bakov 2024

#pragma once
#define MAX_ARMOR_PENETRATION 100.0f
#define MAX_ARMOR 100.0f

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

	float ArmorPenetrationCoefficient = 0.25f;
	float ArmorCoefficient = 0.33f;
};
