// Copyright Kristian Bakov 2024


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetCurrentLevel() const
{
	return 0;
}

FVector ICombatInterface::GetCombatSocketLocation() const
{
	return FVector();
}

