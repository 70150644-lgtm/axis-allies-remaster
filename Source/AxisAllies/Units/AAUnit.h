#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AATypes.h"
#include "AAUnit.generated.h"

class AAATerritory;
class AAANation;

/**
 * Base unit class for WWII RTS
 * Represents infantry, vehicles, planes, and ships
 */
UCLASS()
class AXISALLIES_API AAAUnit : public APawn {
	GENERATED_BODY()

public:
	AAAUnit();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// =============================================
	// Unit Properties
	// =============================================

	/**
	 * Get unit type
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	EUnitType GetUnitType() const { return UnitType; }

	/**
	 * Get unit owner nation
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	ENationID GetOwnerNation() const { return OwnerNation; }

	/**
	 * Get unit stats
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	FUnitStats GetUnitStats() const { return UnitStats; }

	/**
	 * Get current health
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	int32 GetHealth() const { return CurrentHealth; }

	/**
	 * Get max health
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	int32 GetMaxHealth() const { return UnitStats.Health; }

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const;

	// =============================================
	// Territory & Position
	// =============================================

	/**
	 * Get current territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	class AAATerritory* GetCurrentTerritory() const { return CurrentTerritory; }

	/**
	 * Set current territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void SetCurrentTerritory(class AAATerritory* NewTerritory);

	/**
	 * Get territory ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	int32 GetTerritoryID() const;

	// =============================================
	// Movement
	// =============================================

	/**
	 * Move unit to adjacent territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool MoveToTerritory(class AAATerritory* TargetTerritory);

	/**
	 * Get movement range
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	int32 GetMovementRange() const { return UnitStats.Movement; }

	/**
	 * Can unit move this turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool CanMoveThisTurn() const { return !bHasMovedThisTurn; }

	/**
	 * Reset movement for new turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ResetMovement() { bHasMovedThisTurn = false; }

	/**
	 * Get adjacent territories
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void GetAdjacentTerritories(TArray<class AAATerritory*>& OutTerritories) const;

	// =============================================
	// Combat
	// =============================================

	/**
	 * Can unit attack
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAttack() const { return UnitStats.bCanAttack && !bHasAttackedThisTurn; }

	/**
	 * Get attack power
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetAttackPower() const { return UnitStats.Attack; }

	/**
	 * Get defense power
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetDefensePower() const { return UnitStats.Defense; }

	/**
	 * Attack target territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool AttackTerritory(class AAATerritory* TargetTerritory);

	/**
	 * Take damage
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(int32 Damage);

	/**
	 * Heal unit
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Heal(int32 Amount);

	/**
	 * Reset combat for new turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetCombat() { bHasAttackedThisTurn = false; }

	// =============================================
	// Unit State
	// =============================================

	/**
	 * Is unit alive
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	bool IsAlive() const { return CurrentHealth > 0; }

	/**
	 * Destroy unit
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void DestroyUnit();

	/**
	 * Reset unit for new turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	void ResetTurn();

	/**
	 * Get unit condition (health percentage)
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	float GetHealthPercentage() const;

	// =============================================
	// Unit Information
	// =============================================

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const;

	/**
	 * Is unit ground unit (infantry, vehicles, tanks)
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	bool IsGroundUnit() const;

	/**
	 * Is unit air unit (fighters, bombers)
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	bool IsAirUnit() const { return UnitStats.bIsAir; }

	/**
	 * Is unit naval unit (battleships, cruisers, submarines)
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	bool IsNavalUnit() const { return UnitStats.bIsNaval; }

	/**
	 * Get unit icon/visual identifier
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	class UTexture2D* GetUnitIcon() const;

	// =============================================
	// Delegates
	// =============================================

	/**
	 * Called when unit health changes
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, int32, int32);
	FOnHealthChanged OnHealthChanged;

	/**
	 * Called when unit moves
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUnitMoved, class AAATerritory*, class AAATerritory*);
	FOnUnitMoved OnUnitMoved;

	/**
	 * Called when unit attacks
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUnitAttacked, class AAAUnit*, class AAATerritory*);
	FOnUnitAttacked OnUnitAttacked;

	/**
	 * Called when unit is destroyed
	 */
	DECLARE_MULTICAST_DELEGATE(FOnUnitDestroyed);
	FOnUnitDestroyed OnUnitDestroyed;

protected:
	// =============================================
	// Unit Data
	// =============================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	EUnitType UnitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	ENationID OwnerNation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FUnitStats UnitStats;

	UPROPERTY(BlueprintReadOnly, Category = "Unit")
	int32 CurrentHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Unit")
	uint32 UnitID;

	// =============================================
	// Location
	// =============================================

	UPROPERTY()
	class AAATerritory* CurrentTerritory;

	// =============================================
	// State
	// =============================================

	UPROPERTY(BlueprintReadOnly, Category = "Unit")
	bool bHasMovedThisTurn;

	UPROPERTY(BlueprintReadOnly, Category = "Unit")
	bool bHasAttackedThisTurn;

	UPROPERTY(BlueprintReadOnly, Category = "Unit")
	bool bIsInCombat;

	// =============================================
	// Protected Methods
	// =============================================

	/**
	 * Initialize unit stats based on type
	 */
	virtual void InitializeUnitStats();

	/**
	 * Setup unit visuals
	 */
	void SetupUnitVisuals();

	/**
	 * Register unit with game systems
	 */
	void RegisterWithGameSystems();
};