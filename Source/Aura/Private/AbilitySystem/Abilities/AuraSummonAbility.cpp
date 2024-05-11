// Copyright Kristian Bakov 2024


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpreadAngle / NumMinionsToSpawn;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpreadAngle/2, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpreadAngle/2, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for(int32 i = 0; i < NumMinionsToSpawn; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0, 0, 400), ChosenSpawnLocation - FVector(0, 0, 400), ECC_Visibility);
		if(Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	return SpawnLocations;
	
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass() const
{
	if(MinionClasses.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("MinionClasses array is empty!"));
		return nullptr;
	}
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
