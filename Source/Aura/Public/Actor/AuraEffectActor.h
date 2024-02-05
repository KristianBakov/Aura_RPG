// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FGameplayEffectContainer
{
	GENERATED_BODY()

	FGameplayEffectContainer(): EffectApplicationPolicy(EEffectApplicationPolicy::ApplyOnOverlap),
	EffectRemovalPolicy(EEffectRemovalPolicy::DoNotRemove)
	{
	}

	FGameplayEffectContainer(EEffectApplicationPolicy EAP, EEffectRemovalPolicy ERP ):
	EffectApplicationPolicy(EAP), EffectRemovalPolicy(ERP)
	{
	}
	FGameplayEffectContainer(TSubclassOf<UGameplayEffect> GE, EEffectApplicationPolicy EAP, EEffectRemovalPolicy ERP ):
	GameplayEffectClass(GE), EffectApplicationPolicy(EAP), EffectRemovalPolicy(ERP)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;
	/** Only used for Infinite Gameplay Effects **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void AddGameplayEffect(const FGameplayEffectContainer& GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void RemoveGameplayEffect(const FGameplayEffectContainer& GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectContainer GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FGameplayEffectContainer> GameplayEffects;
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
};
