// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
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
	EffectRemovalPolicy(EEffectRemovalPolicy::DoNotRemove) {}
	FGameplayEffectContainer(EEffectApplicationPolicy EAP, EEffectRemovalPolicy ERP ):
	EffectApplicationPolicy(EAP), EffectRemovalPolicy(ERP) {}
	FGameplayEffectContainer(TSubclassOf<UGameplayEffect> GE, EEffectApplicationPolicy EAP, EEffectRemovalPolicy ERP ):
	GameplayEffectClass(GE), EffectApplicationPolicy(EAP), EffectRemovalPolicy(ERP) {}

	bool operator==(const FGameplayEffectContainer& Other) const
	{
		return GameplayEffectClass == Other.GameplayEffectClass &&
			   EffectApplicationPolicy == Other.EffectApplicationPolicy &&
			   EffectRemovalPolicy == Other.EffectRemovalPolicy;
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
	void AddGameplayEffectToList(const FGameplayEffectContainer& GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void RemoveGameplayEffectFromList(const FGameplayEffectContainer& GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectContainer GameplayEffectContainer);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FGameplayEffectContainer> GameplayEffects;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

private:
	void TryRemoveActiveInfiniteGameplayEffectFromTarget(AActor* TargetActor);
};
