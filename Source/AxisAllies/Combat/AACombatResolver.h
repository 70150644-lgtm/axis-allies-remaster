#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AATypes.h"
#include "AACombatResolver.generated.h"

class AAAUnit;
class AAATerritory;

/**
 * Handles combat resolution with dice rolls and casualty calculation
 */
UCLASS()
class AXISALLIES_API AACombatResolver : public AActor {
	GENERATED_BODY()

public:
	AACombatResolver();

	virtual void BeginPlay() override;

	// =============================================
	// Combat Resolution
	// =============================================

	/**
	 * Resolve combat between attacking and defending units
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FCombatResult ResolveCombat(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits,
		class AAATerritory* BattleLocation
	);

	/**
	 * Single round of combat
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FCombatResult ResolveCombatRound(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits
	);

	// =============================================
	// Dice Rolling
	// =============================================

	/**
	 * Roll attack dice for unit
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 RollAttackDice(class AAAUnit* Unit);

	/**
	 * Roll defense dice for unit
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 RollDefenseDice(class AAAUnit* Unit);

	/**
	 * Roll multiple dice
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	TArray<int32> RollMultipleDice(int32 DiceCount);

	// =============================================
	// Casualty Calculation
	// =============================================

	/**
	 * Calculate casualties from hits
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CalculateCasualties(
		TArray<class AAAUnit*>& Units,
		int32 Hits,
		TArray<class AAAUnit*>& OutRemovedUnits
	);

	/**
	 * Select unit as casualty
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	class AAAUnit* SelectCasualtyUnit(const TArray<class AAAUnit*>& Units) const;

	// =============================================
	// Combat Statistics
	// =============================================

	/**
	 * Get unit hit probability
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetUnitHitProbability(class AAAUnit* Unit, bool bAttacking) const;

	/**
	 * Get expected casualties
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetExpectedCasualties(const TArray<class AAAUnit*>& Units, bool bAttacking) const;

	/**
	 * Calculate combat odds
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CalculateCombatOdds(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits,
		float& OutAttackerWinProbability
	);

protected:
	// =============================================
	// Combat Logic
	// =============================================

	/**
	 * Determine hit threshold for unit type
	 */
	int32 GetHitThreshold(EUnitType UnitType, bool bAttacking) const;

	/**
	 * Get attack modifier for unit
	 */
	float GetAttackModifier(class AAAUnit* Unit) const;

	/**
	 * Get defense modifier for unit
	 */
	float GetDefenseModifier(class AAAUnit* Unit) const;

	/**
	 * Apply terrain bonuses
	 */
	void ApplyTerrainBonuses(
		const TArray<class AAAUnit*>& DefendingUnits,
		class AAATerritory* BattleLocation,
		int32& OutDefenseBonus
	);

	/**
	 * Check for unit special abilities (air cover, etc)
	 */
	void CheckSpecialAbilities(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits,
		int32& OutAttackerBonus,
		int32& OutDefenderBonus
	);

	/**
	 * Log combat result
	 */
	void LogCombatResult(const FCombatResult& Result);

	// =============================================
	// Combat Configuration
	// =============================================

	// Unit type hit thresholds (roll this or higher = hit)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TMap<EUnitType, int32> UnitAttackThresholds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TMap<EUnitType, int32> UnitDefenseThresholds;

	// Unit modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TMap<EUnitType, float> UnitAttackModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TMap<EUnitType, float> UnitDefenseModifiers;
};