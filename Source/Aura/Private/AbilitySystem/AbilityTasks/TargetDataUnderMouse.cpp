// Copyright Kristian Bakov 2024


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	FHitResult CursorHit;
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if(!PlayerController) return;
	 
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(CursorHit.bBlockingHit)
	{
		ValidData.Broadcast(CursorHit.Location);
	}
}
