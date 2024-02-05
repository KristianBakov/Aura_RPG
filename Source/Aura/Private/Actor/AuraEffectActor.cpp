// Copyright Kristian Bakov 2024


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::AddGameplayEffect(const FGameplayEffectContainer& GameplayEffectContainer)
{
	if(GameplayEffectContainer.GameplayEffectClass)
	{
		GameplayEffects.Add(GameplayEffectContainer);
	}
}

void AAuraEffectActor::RemoveGameplayEffect(const FGameplayEffectContainer& GameplayEffectContainer)
{
	if(GameplayEffectContainer.GameplayEffectClass)
	{
		GameplayEffects.Remove(GameplayEffectContainer);
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectContainer GameplayEffectContainer)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr) return;

	check(GameplayEffectContainer.GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectContainer.GameplayEffectClass, 1.f, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite =  EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && GameplayEffectContainer.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const FGameplayEffectContainer GameplayEffectContainer: GameplayEffects)
	{
		check (GameplayEffectContainer.GameplayEffectClass);

		if(GameplayEffectContainer.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, GameplayEffectContainer);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const FGameplayEffectContainer GameplayEffectContainer: GameplayEffects)
	{
		check (GameplayEffectContainer.GameplayEffectClass);

		if(GameplayEffectContainer.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, GameplayEffectContainer);
		}

		if(GameplayEffectContainer.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if(!IsValid(TargetASC)) return;

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (auto HandlePair : ActiveEffectHandles)
			{
				if(TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}

