// Copyright Kristian Bakov 2024


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/AuraLevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(this->AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(this->AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);});

	if(UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if(AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		AuraASC->EffectAssetTagsApplied.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for(const FGameplayTag& Tag : AssetTags)
				{
					if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Message")))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);	
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraASC) const
{
	//TODO: get informatuon about all given abilities, look up their ability info and broadcast to widgets
	if(!AuraASC->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		//need a way to figure out ability tag for given ability spec
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoTag(AuraASC->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraASC->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	}
	);
	AuraASC->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = AuraPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("LevelUpInfo is not set in player state"));

	const int32 Level = LevelUpInfo->GetLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if(Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		//divide current level's XP by current level's max XP
		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
