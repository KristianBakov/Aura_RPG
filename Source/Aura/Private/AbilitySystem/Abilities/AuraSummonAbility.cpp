// Copyright Kristian Bakov 2024


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinionsToSpawn;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread/2, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for(int32 i = 0; i < NumMinionsToSpawn; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
		
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18, 12, FColor::Cyan, false, 3);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.0f, FLinearColor::Green,3.0f);
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5, 12, FColor::Red, false, 3);
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5, 12, FColor::Red, false, 3);
	}
	return SpawnLocations;
	
}
