// Copyright Kristian Bakov 2024


#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if(Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if(bLogNotFound) UE_LOG(LogAura, Error, TEXT("AbilityInfo [%s] with tag [%s] not found!"), *GetNameSafe(this),  *AbilityTag.ToString())

	return FAuraAbilityInfo();
}
