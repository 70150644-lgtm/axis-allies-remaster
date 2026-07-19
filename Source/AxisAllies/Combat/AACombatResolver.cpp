#include "Combat/AACombatResolver.h"
#include "Units/AAUnit.h"
#include "Kismet/GameplayStatics.h"

AACombatResolver::AACombatResolver()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize unit thresholds (roll this or higher to hit)
	UnitAttackThresholds.Add(EUnitType::Infantry, 3);      // Need 3+ to hit
	UnitAttackThresholds.Add(EUnitType::Armor, 3);         // Need 3+ to hit
	UnitAttackThresholds.Add(EUnitType::Artillery, 4);     // Need 4+ to hit
	UnitAttackThresholds.Add(EUnitType::Fighter, 2);       // Need 2+ to hit
	UnitAttackThresholds.Add(EUnitType::Bomber, 2);        // Need 2+ to hit
	UnitAttackThresholds.Add(EUnitType::Transport, 5);     // Need 5+ to hit
	UnitAttackThresholds.Add(EUnitType::Battleship, 2);    // Need 2+ to hit
	UnitAttackThresholds.Add(EUnitType::Cruiser, 3);       // Need 3+ to hit
	UnitAttackThresholds.Add(EUnitType::Submarine, 3);     // Need 3+ to hit

	// Defense thresholds
	UnitDefenseThresholds.Add(EUnitType::Infantry, 2);     // Need 2+ to defend
	UnitDefenseThresholds.Add(EUnitType::Armor, 3);        // Need 3+ to defend
	UnitDefenseThresholds.Add(EUnitType::Artillery, 3);    // Need 3+ to defend
	UnitDefenseThresholds.Add(EUnitType::Fighter, 3);      // Need 3+ to defend
	UnitDefenseThresholds.Add(EUnitType::Bomber, 4);       // Need 4+ to defend
	UnitDefenseThresholds.Add(EUnitType::Transport, 4);    // Need 4+ to defend
	UnitDefenseThresholds.Add(EUnitType::Battleship, 2);   // Need 2+ to defend
	UnitDefenseThresholds.Add(EUnitType::Cruiser, 3);      // Need 3+ to defend
	UnitDefenseThresholds.Add(EUnitType::Submarine, 3);    // Need 3+ to defend

	// Attack modifiers
	UnitAttackModifiers.Add(EUnitType::Infantry, 1.0f);
	UnitAttackModifiers.Add(EUnitType::Armor, 1.5f);       // Tanks deal more damage
	UnitAttackModifiers.Add(EUnitType::Artillery, 1.2f);
	UnitAttackModifiers.Add(EUnitType::Fighter, 1.0f);
	UnitAttackModifiers.Add(EUnitType::Bomber, 1.8f);      // Bombers deal extra damage
	UnitAttackModifiers.Add(EUnitType::Transport, 0.0f);   // Cannot attack
	UnitAttackModifiers.Add(EUnitType::Battleship, 1.6f);
	UnitAttackModifiers.Add(EUnitType::Cruiser, 1.3f);
	UnitAttackModifiers.Add(EUnitType::Submarine, 1.2f);

	// Defense modifiers
	UnitDefenseModifiers.Add(EUnitType::Infantry, 1.0f);
	UnitDefenseModifiers.Add(EUnitType::Armor, 1.4f);
	UnitDefenseModifiers.Add(EUnitType::Artillery, 1.1f);
	UnitDefenseModifiers.Add(EUnitType::Fighter, 1.0f);
	UnitDefenseModifiers.Add(EUnitType::Bomber, 0.5f);     // Poor defense
	UnitDefenseModifiers.Add(EUnitType::Transport, 0.5f);  // Poor defense
	UnitDefenseModifiers.Add(EUnitType::Battleship, 1.5f);
	UnitDefenseModifiers.Add(EUnitType::Cruiser, 1.2f);
	UnitDefenseModifiers.Add(EUnitType::Submarine, 0.8f);
}

void AACombatResolver::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AACombatResolver: Initialized with combat tables"));
}

FCombatResult AACombatResolver::ResolveCombat(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits,
	class AAATerritory* BattleLocation)
{
	FCombatResult Result;
	Result.AttackerCasualties = 0;
	Result.DefenderCasualties = 0;
	Result.bAttackerVictory = false;

	if (AttackingUnits.Num() == 0 || DefendingUnits.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AACombatResolver: Invalid combat - no units"));
		return Result;
	}

	// Continue combat rounds until one side is eliminated
	TArray<AAAUnit*> TempAttackers = AttackingUnits;
	TArray<AAAUnit*> TempDefenders = DefendingUnits;

	int32 RoundCount = 0;
	while (TempAttackers.Num() > 0 && TempDefenders.Num() > 0 && RoundCount < 10)
	{
		FCombatResult RoundResult = ResolveCombatRound(TempAttackers, TempDefenders);

		Result.AttackerCasualties += RoundResult.AttackerCasualties;
		Result.DefenderCasualties += RoundResult.DefenderCasualties;

		RoundCount++;
	}

	Result.bAttackerVictory = TempAttackers.Num() > 0;

	LogCombatResult(Result);

	return Result;
}

FCombatResult AACombatResolver::ResolveCombatRound(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits)
{
	FCombatResult Result;
	Result.AttackerCasualties = 0;
	Result.DefenderCasualties = 0;

	// Roll attack dice
	int32 AttackerHits = 0;
	for (AAAUnit* Unit : AttackingUnits)
	{
		if (Unit)
		{
			int32 Roll = RollAttackDice(Unit);
			if (Roll > 0)
			{
				AttackerHits += Roll;
			}
		}
	}

	// Roll defense dice
	int32 DefenderHits = 0;
	for (AAAUnit* Unit : DefendingUnits)
	{
		if (Unit)
		{
			int32 Roll = RollDefenseDice(Unit);
			if (Roll > 0)
			{
				DefenderHits += Roll;
			}
		}
	}

	// Calculate casualties
	Result.AttackerCasualties = DefenderHits;
	Result.DefenderCasualties = AttackerHits;

	UE_LOG(LogTemp, Warning, TEXT("AACombatResolver: Combat round - Attacker hits: %d, Defender hits: %d"), 
		AttackerHits, DefenderHits);

	return Result;
}

int32 AACombatResolver::RollAttackDice(AAAUnit* Unit)
{
	if (!Unit)
	{
		return 0;
	}

	EUnitType UnitType = Unit->GetUnitType();
	int32 Threshold = GetHitThreshold(UnitType, true);

	// Roll 1d6
	int32 Roll = FMath::RandRange(1, 6);

	// Check if hit
	if (Roll >= Threshold)
	{
		return 1;
	}

	return 0;
}

int32 AACombatResolver::RollDefenseDice(AAAUnit* Unit)
{
	if (!Unit)
	{
		return 0;
	}

	EUnitType UnitType = Unit->GetUnitType();
	int32 Threshold = GetHitThreshold(UnitType, false);

	// Roll 1d6
	int32 Roll = FMath::RandRange(1, 6);

	// Check if hit
	if (Roll >= Threshold)
	{
		return 1;
	}

	return 0;
}

TArray<int32> AACombatResolver::RollMultipleDice(int32 DiceCount)
{
	TArray<int32> Rolls;

	for (int32 i = 0; i < DiceCount; ++i)
	{
		Rolls.Add(FMath::RandRange(1, 6));
	}

	return Rolls;
}

void AACombatResolver::CalculateCasualties(
	TArray<AAAUnit*>& Units,
	int32 Hits,
	TArray<AAAUnit*>& OutRemovedUnits)
{
	OutRemovedUnits.Empty();

	// Select units as casualties
	for (int32 i = 0; i < Hits && Units.Num() > 0; ++i)
	{
		AAAUnit* Casualty = SelectCasualtyUnit(Units);
		if (Casualty)
		{
			Units.RemoveSingle(Casualty);
			OutRemovedUnits.Add(Casualty);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AACombatResolver: %d casualties"), OutRemovedUnits.Num());
}

AAAUnit* AACombatResolver::SelectCasualtyUnit(const TArray<AAAUnit*>& Units) const
{
	if (Units.Num() == 0)
	{
		return nullptr;
	}

	// Random selection (simplified - could use more complex logic)
	int32 Index = FMath::RandRange(0, Units.Num() - 1);
	return Units[Index];
}

float AACombatResolver::GetUnitHitProbability(AAAUnit* Unit, bool bAttacking) const
{
	if (!Unit)
	{
		return 0.0f;
	}

	EUnitType UnitType = Unit->GetUnitType();
	int32 Threshold = GetHitThreshold(UnitType, bAttacking);

	// Probability = (7 - threshold) / 6
	return (7.0f - Threshold) / 6.0f;
}

int32 AACombatResolver::GetExpectedCasualties(const TArray<AAAUnit*>& Units, bool bAttacking) const
{
	if (Units.Num() == 0)
	{
		return 0;
	}

	int32 TotalHitProbability = 0;
	for (AAAUnit* Unit : Units)
	{
		if (Unit)
		{
			float Probability = GetUnitHitProbability(Unit, bAttacking);
			TotalHitProbability += FMath::RoundToInt(Probability * 100.0f);
		}
	}

	return FMath::RoundToInt(TotalHitProbability / 100.0f);
}

void AACombatResolver::CalculateCombatOdds(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits,
	float& OutAttackerWinProbability)
{
	// Simplified calculation
	int32 AttackerStrength = 0;
	int32 DefenderStrength = 0;

	for (AAAUnit* Unit : AttackingUnits)
	{
		if (Unit)
		{
			AttackerStrength += Unit->GetAttackPower();
		}
	}

	for (AAAUnit* Unit : DefendingUnits)
	{
		if (Unit)
		{
			DefenderStrength += Unit->GetDefensePower();
		}
	}

	if (AttackerStrength + DefenderStrength == 0)
	{
		OutAttackerWinProbability = 0.5f;
	}
	else
	{
		OutAttackerWinProbability = (float)AttackerStrength / (AttackerStrength + DefenderStrength);
	}
}

int32 AACombatResolver::GetHitThreshold(EUnitType UnitType, bool bAttacking) const
{
	const TMap<EUnitType, int32>& ThresholdMap = bAttacking ? UnitAttackThresholds : UnitDefenseThresholds;
	const int32* ThresholdPtr = ThresholdMap.Find(UnitType);

	return ThresholdPtr ? *ThresholdPtr : 4;
}

float AACombatResolver::GetAttackModifier(AAAUnit* Unit) const
{
	if (!Unit)
	{
		return 1.0f;
	}

	const float* ModifierPtr = UnitAttackModifiers.Find(Unit->GetUnitType());
	return ModifierPtr ? *ModifierPtr : 1.0f;
}

float AACombatResolver::GetDefenseModifier(AAAUnit* Unit) const
{
	if (!Unit)
	{
		return 1.0f;
	}

	const float* ModifierPtr = UnitDefenseModifiers.Find(Unit->GetUnitType());
	return ModifierPtr ? *ModifierPtr : 1.0f;
}

void AACombatResolver::ApplyTerrainBonuses(
	const TArray<AAAUnit*>& DefendingUnits,
	class AAATerritory* BattleLocation,
	int32& OutDefenseBonus)
{
	OutDefenseBonus = 0;

	// TODO: Apply terrain defense bonuses
}

void AACombatResolver::CheckSpecialAbilities(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits,
	int32& OutAttackerBonus,
	int32& OutDefenderBonus)
{
	OutAttackerBonus = 0;
	OutDefenderBonus = 0;

	// TODO: Check for special abilities like air cover
}

void AACombatResolver::LogCombatResult(const FCombatResult& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("AACombatResolver: Combat ended - Attacker: %d casualties, Defender: %d casualties, Attacker won: %s"),
		Result.AttackerCasualties,
		Result.DefenderCasualties,
		Result.bAttackerVictory ? TEXT("Yes") : TEXT("No"));
}
