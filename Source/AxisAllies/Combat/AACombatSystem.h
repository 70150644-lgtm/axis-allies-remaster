#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AATypes.h"
#include "AACombatSystem.generated.h"

class AACombatResolver;
class AAATerritory;
class AAAUnit;

/**
 * Main combat system - orchestrates battle resolution
 */
UCLASS()
class AXISALLIES_API AACombatSystem : public AActor {
	GENERATED_BODY()

public:
	AACombatSystem();

	virtual void BeginPlay() override;

	// =============================================
	// Combat Initiation
	// =============================================

	/**
	 * Start combat in a territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool StartCombat(
		class AAAUnit* AttackingUnit,
		class AAATerritory* DefendingTerritory
	);

	/**
	 * Resolve ongoing combat
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FCombatResult ResolveCombat(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits,
		class AAATerritory* BattleLocation,
		bool bAutoResolve = false
	);

	/**
	 * Retreat from combat
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RetreatFromCombat(class AAAUnit* AttackingUnit);

	// =============================================
	// Combat State
	// =============================================

	/**
	 * Is combat active in territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsCombatActive(int32 TerritoryID) const;

	/**
	 * Get active combats
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void GetActiveCombats(TArray<int32>& OutTerritoryIDs) const;

	/**
	 * Get units involved in combat
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void GetCombatUnits(
		int32 TerritoryID,
		TArray<class AAAUnit*>& OutAttackers,
		TArray<class AAAUnit*>& OutDefenders
	) const;

	// =============================================
	// Combat Statistics
	// =============================================

	/**
	 * Calculate combat odds
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CalculateCombatOdds(
		const TArray<class AAAUnit*>& AttackingUnits,
		const TArray<class AAAUnit*>& DefendingUnits,
		float& OutAttackerWinProbability,
		int32& OutExpectedAttackerCasualties,
		int32& OutExpectedDefenderCasualties
	);

	/**
	 * Get combat history
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FString GetCombatLog(int32 TerritoryID) const;

	// =============================================
	// Delegates
	// =============================================

	/**
	 * Called when combat starts
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCombatStarted, int32, const TArray<class AAAUnit*>&);
	FOnCombatStarted OnCombatStarted;

	/**
	 * Called when combat round completes
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCombatRoundResolved, int32, const FCombatResult&);
	FOnCombatRoundResolved OnCombatRoundResolved;

	/**
	 * Called when combat ends
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCombatEnded, int32, class AAAUnit*);
	FOnCombatEnded OnCombatEnded;

	/**
	 * Called when territory captured
	 */
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTerritoryCaptured, int32, class AAAUnit*, class AAATerritory*);
	FOnTerritoryCaptured OnTerritoryCaptured;

	// =============================================
	// Combat Resolver
	// =============================================

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AACombatResolver* GetCombatResolver() const { return CombatResolverRef; }

protected:
	// =============================================
	// Combat State Tracking
	// =============================================

	struct FCombatState {
		int32 TerritoryID;
		TArray<class AAAUnit*> AttackingUnits;
		TArray<class AAAUnit*> DefendingUnits;
		int32 RoundNumber;
		FString CombatLog;
		bool bResolved;
	};

	UPROPERTY()
	TMap<int32, FCombatState> ActiveCombats;

	UPROPERTY()
	class AACombatResolver* CombatResolverRef;

	// =============================================
	// Combat History
	// =============================================

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	TMap<int32, FString> CombatHistory;

	// =============================================
	// Settings
	// =============================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAutoResolveCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAnimateCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float CombatAnimationSpeed;

	// =============================================
	// Protected Methods
	// =============================================

	/**
	 * End combat in territory
	 */
	void EndCombat(int32 TerritoryID, class AAAUnit* Conqueror);

	/**
	 * Remove casualties from unit array
	 */
	void RemoveCasualties(
		TArray<class AAAUnit*>& Units,
		const TArray<class AAAUnit*>& Casualties
	);

	/**
	 * Occupy territory with victorious unit
	 */
	void OccupyTerritory(class AAAUnit* Conqueror, class AAATerritory* Territory);

	/**
	 * Log combat action
	 */
	void LogCombatAction(int32 TerritoryID, const FString& Action);
};