#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsBlockedHit() const { return bIsBlockedHit; }
	void SetBlockedHit(const bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }

	bool IsCriticalHit() const { return bIsCriticalHit; }
	void SetCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;
};