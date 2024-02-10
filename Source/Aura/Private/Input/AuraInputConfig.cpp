// Copyright Kristian Bakov 2024


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                   const bool bLogNotFound) const
{
	for( const FAuraInputAction& InputActionStruct : AbilityInputActions)
	{
		if(InputActionStruct.InputAction && InputTag.MatchesTagExact(InputActionStruct.InputTag))
		{
			return InputActionStruct.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("No input action found for tag [%s] on config [%s]"),
			*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
