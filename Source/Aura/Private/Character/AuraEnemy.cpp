// Copyright Kristian Bakov 2024


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bIsHighlighted = true;
	UE_LOG(	LogTemp, Warning, TEXT("HighlightActor"));
}

void AAuraEnemy::UnhighlightActor()
{
	bIsHighlighted = false;
	UE_LOG(LogTemp, Warning, TEXT("UnhighlightActor"));	
}
