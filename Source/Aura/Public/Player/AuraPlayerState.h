// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*NewValue*/);

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnXPChangedDelegate;
	
	FORCEINLINE int32 GetCurrentLevel() const { return Level; }
	FORCEINLINE int32 GetCurrentXP() const { return XP; }

	void SetLevel(int32 NewLevel);
	void SetXP(int32 NewXP);
	void AddToXP(int32 AmountToAdd);
	void AddToLevel(int32 AmountToAdd);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level, Category = "Player State")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing= OnRep_XP, Category = "Player State")
	int32 XP = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
