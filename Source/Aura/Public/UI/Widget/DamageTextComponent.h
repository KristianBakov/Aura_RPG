// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Damage Text")
	void SetDamageText(float Damage, bool bBlockedHit, bool bCriticalHit);
};
