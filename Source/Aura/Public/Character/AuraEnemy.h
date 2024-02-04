// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/TargetInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public ITargetInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	// ITargetInterface
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	// End ITargetInterface

	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted = false;

protected:
	virtual void BeginPlay() override;
};