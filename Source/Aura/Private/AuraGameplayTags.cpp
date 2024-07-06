// Copyright Kristian Bakov 2024


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::Instance;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	
	Instance.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Strength"),
	FString("Increases Physical Damage")
	);

	Instance.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Intelligence"),
	FString("Increases magical damage")
	);

	Instance.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Resilience"),
FString("Increases armor and armor penetration")
	);

	Instance.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Vigor"),
FString("Increases health and health regeneration")
	);

	
	/*
	* Secondary Attributes
	*/

	Instance.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance")
		);

	Instance.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance")
		);

	Instance.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half")
		);

	Instance.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus")
		);

	Instance.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored")
		);

	Instance.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces Critical Hit Chance of attacking enemies")
		);

	Instance.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated every 1 second")
		);

	Instance.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regenerated every 1 second")
		);

	Instance.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable")
		);

	Instance.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of Mana obtainable")
		);

	/*
	* Meta Attributes
	*/

	Instance.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Meta.IncomingXP"),
	FString("Incoming XP tag")
	);

	/*
	* Input Tags
	*/

	Instance.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Left Mouse Button")
		);

	Instance.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag( 
		FName("InputTag.RMB"),
		FString("Right Mouse Button")
		);

	Instance.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input tag for 1 key")
		);

	Instance.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.2"),
	FString("Input tag for 2 key")
	);

	Instance.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.3"),
	FString("Input tag for 3 key")
	);

	Instance.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.4"),
	FString("Input tag for 4 key")
	);

	Instance.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"),
	FString("Tag for damage")
	);

	/*
	* Damage Types
	*/

	Instance.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Fire"),
	FString("Fire Damage")
	);
	
	Instance.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Lightning"),
	FString("Lightning Damage")
	);

	Instance.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
FString("Arcane Damage")
	);

	Instance.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Physical"),
	FString("Physical Damage")
	);

	/*
	* Resistances
	*/

	Instance.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Fire"),
	FString("Resistance to Fire Damage")
	);
	
	Instance.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Lightning"),
	FString("Resistance to Lightning Damage")
	);

	Instance.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"),
FString("Resistance to Arcane Damage")
	);

	Instance.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Physical"),
	FString("Resistance to Physical Damage")
	);

	/*
	* Abilities
	*/

	Instance.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"),
	FString("Attack ability tag")
	);
	
	Instance.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Summon"),
	FString("Summon ability tag")
	);

	Instance.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Fire.FireBolt"),
	FString("FireBolt ability tag")
	);

	/*
	* Cooldown
	*/

	Instance.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Cooldown.Fire.FireBolt"),
	FString("FireBolt cooldown tag")
	);

	/*
	* Combat sockets
	*/

	Instance.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Weapon"),
	FString("Weapon combat socket")
	);

	Instance.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.RightHand"),
	FString("Right hand combat socket")
	);

	Instance.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.LeftHand"),
	FString("Left hand combat socket")
	);

	Instance.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Tail"),
	FString("Tail combat socket")
	);

	/*
	* Montage attack tags
	*/

	Instance.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.1"),
	FString("Attack 1 tag")
	);

	Instance.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.2"),
	FString("Attack 2 tag")
	);

	Instance.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.3"),
	FString("Attack 3 tag")
	);

	Instance.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.4"),
	FString("Attack 4 tag")
	);

	/*
	* Map of Damage types to Resistances
	*/

	Instance.DamageTypesToResistances.Add(Instance.Damage_Fire, Instance.Attributes_Resistance_Fire);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Lightning, Instance.Attributes_Resistance_Lightning);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Arcane, Instance.Attributes_Resistance_Arcane);
	Instance.DamageTypesToResistances.Add(Instance.Damage_Physical, Instance.Attributes_Resistance_Physical);

	/*
	* Effects
	*/
	
	Instance.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effects.HitReact"),
	FString("Effect tag for hit reaction")
	);
}
