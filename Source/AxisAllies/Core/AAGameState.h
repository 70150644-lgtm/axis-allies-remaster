#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AATypes.h"
#include "AAGameState.generated.h"

class AAANation;
class AAGameBoard;

/**
 * Main game state actor
 * Replicated to all clients and manages game state
 */
UCLASS()
class AXISALLIES_API AAGameState : public AGameStateBase {
	GENERATED_BODY()

public:
	AAGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// =============================================
	// Game State Accessors
	// =============================================

	/**
	 * Get all nations in the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	TArray<class AAANation*> GetNations() const { return Nations; }

	/**
	 * Get nation by ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	class AAANation* GetNation(ENationID NationID) const;

	/**
	 * Get current turn number
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetTurnNumber() const { return TurnNumber; }

	/**
	 * Get current player nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	class AAANation* GetCurrentPlayerNation() const;

	/**
	 * Get game board
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	class AAGameBoard* GetGameBoard() const { return GameBoardRef; }

	// =============================================
	// Nation Management
	// =============================================

	/**
	 * Add nation to game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddNation(class AAANation* NewNation);

	/**
	 * Remove nation from game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void RemoveNation(ENationID NationID);

	/**
	 * Get player count
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetPlayerCount() const { return Nations.Num(); }

	// =============================================
	// Resource Management
	// =============================================

	/**
	 * Get nation resources (IPC)
	 */
	UFUNCTION(BlueprintCallable, Category = "Economy")
	int32 GetNationResources(ENationID NationID) const;

	/**
	 * Add resources to nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Economy")
	void AddNationResources(ENationID NationID, int32 Amount);

	/**
	 * Subtract resources from nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Economy")
	bool SubtractNationResources(ENationID NationID, int32 Amount);

	// =============================================
	// Territory Management
	// =============================================

	/**
	 * Get territories controlled by nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Territories")
	int32 GetNationTerritoryCount(ENationID NationID) const;

	/**
	 * Get total income for nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Territories")
	int32 GetNationIncome(ENationID NationID) const;

	/**
	 * Transfer territory ownership
	 */
	UFUNCTION(BlueprintCallable, Category = "Territories")
	void TransferTerritoryOwnership(int32 TerritoryID, ENationID NewOwner);

	// =============================================
	// Unit Management
	// =============================================

	/**
	 * Get unit count for nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Units")
	int32 GetNationUnitCount(ENationID NationID) const;

	/**
	 * Get unit count by type for nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Units")
	int32 GetNationUnitCountByType(ENationID NationID, EUnitType UnitType) const;

	/**
	 * Register unit with game state
	 */
	UFUNCTION(BlueprintCallable, Category = "Units")
	void RegisterUnit(class AAAUnit* Unit);

	/**
	 * Unregister unit from game state
	 */
	UFUNCTION(BlueprintCallable, Category = "Units")
	void UnregisterUnit(class AAAUnit* Unit);

	/**
	 * Get units in territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Units")
	void GetUnitsInTerritory(int32 TerritoryID, TArray<class AAAUnit*>& OutUnits) const;

	// =============================================
	// Game Statistics
	// =============================================

	/**
	 * Get nation statistics
	 */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	FPlayerStats GetNationStats(ENationID NationID) const;

	/**
	 * Get total military strength for nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetNationMilitaryStrength(ENationID NationID) const;

	/**
	 * Get all game statistics
	 */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	TMap<ENationID, FPlayerStats> GetAllStats() const;

protected:
	// =============================================
	// Game State Data
	// =============================================

	UPROPERTY(Replicated)
	TArray<class AAANation*> Nations;

	UPROPERTY(Replicated)
	int32 TurnNumber;

	UPROPERTY(Replicated)
	int32 CurrentPlayerIndex;

	UPROPERTY()
	class AAGameBoard* GameBoardRef;

	// =============================================
	// Unit Tracking
	// =============================================

	UPROPERTY()
	TMap<uint32, class AAAUnit*> AllUnits;

	UPROPERTY()
	TMap<ENationID, TArray<class AAAUnit*>> NationUnits;

	UPROPERTY()
	TMap<int32, TArray<class AAAUnit*>> TerritoryUnits;

	// =============================================
	// Resource Tracking
	// =============================================

	UPROPERTY(Replicated)
	TMap<ENationID, int32> NationResources;

	// =============================================
	// Protected Methods
	// =============================================

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Update military strength for nation
	 */
	void UpdateMilitaryStrength(ENationID NationID);

	/**
	 * Calculate military strength
	 */
	float CalculateMilitaryStrength(ENationID NationID) const;
};