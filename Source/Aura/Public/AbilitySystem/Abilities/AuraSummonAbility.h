// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Summoning")
	TArray<FVector> GetSpawnLocations();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summoning")
	int32 NumMinionsToSpawn = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summoning")
	float MinSpawnDistance = 50.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summoning")
	float SpawnSpreadAngle = 90.0f;
};
