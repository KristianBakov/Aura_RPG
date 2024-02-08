// Copyright Kristian Bakov 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura Gameplay Tags
 *
 * Singleton class that holds all the gameplay tags used in the game.
 */
struct FAuraGameplayTags
{
public:
 static const FAuraGameplayTags& Get() { return Instance;}
 static void InitializeNativeGameplayTags();

protected:

private:
 static FAuraGameplayTags Instance;
};