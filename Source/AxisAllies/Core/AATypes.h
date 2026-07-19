#pragma once

#include "CoreMinimal.h"
#include "AATypes.generated.h"

/**
 * Axis & Allies - Core Type Definitions
 */

// =============================================
// Enumerations
// =============================================

/**
 * Unit types in the game
 */
UENUM(BlueprintType)
enum class EUnitType : uint8 {
	Infantry UMETA(DisplayName = "Infantry"),
	Armor UMETA(DisplayName = "Armor"),
	Artillery UMETA(DisplayName = "Artillery"),
	Fighter UMETA(DisplayName = "Fighter"),
	Bomber UMETA(DisplayName = "Bomber"),
	Transport UMETA(DisplayName = "Transport"),
	Battleship UMETA(DisplayName = "Battleship"),
	Cruiser UMETA(DisplayName = "Cruiser"),
	Submarine UMETA(DisplayName = "Submarine"),
	MAX UMETA(Hidden)
};

/**
 * Playable nations
 */
UENUM(BlueprintType)
enum class ENationID : uint8 {
	Germany UMETA(DisplayName = "Germany"),
	Japan UMETA(DisplayName = "Japan"),
	Italy UMETA(DisplayName = "Italy"),
	SovietUnion UMETA(DisplayName = "Soviet Union"),
	UnitedStates UMETA(DisplayName = "United States"),
	UnitedKingdom UMETA(DisplayName = "United Kingdom"),
	Neutral UMETA(DisplayName = "Neutral"),
	MAX UMETA(Hidden)
};

/**
 * Game phases
 */
UENUM(BlueprintType)
enum class EGamePhase : uint8 {
	Purchase UMETA(DisplayName = "Purchase Phase"),
	Deploy UMETA(DisplayName = "Deploy Phase"),
	Combat UMETA(DisplayName = "Combat Phase"),
	Movement UMETA(DisplayName = "Movement Phase"),
	EndTurn UMETA(DisplayName = "End Turn"),
	MAX UMETA(Hidden)
};

/**
 * Game difficulty levels
 */
UENUM(BlueprintType)
enum class EGameDifficulty : uint8 {
	Easy UMETA(DisplayName = "Easy"),
	Medium UMETA(DisplayName = "Medium"),
	Hard UMETA(DisplayName = "Hard"),
	Expert UMETA(DisplayName = "Expert"),
	MAX UMETA(Hidden)
};

/**
 * Game state
 */
UENUM(BlueprintType)
enum class EGameState : uint8 {
	Menu UMETA(DisplayName = "Main Menu"),
	Setup UMETA(DisplayName = "Game Setup"),
	Playing UMETA(DisplayName = "Playing"),
	Paused UMETA(DisplayName = "Paused"),
	GameOver UMETA(DisplayName = "Game Over"),
	MAX UMETA(Hidden)
};

/**
 * Victory conditions
 */
UENUM(BlueprintType)
enum class EVictoryCondition : uint8 {
	Military UMETA(DisplayName = "Military Victory"),
	Economic UMETA(DisplayName = "Economic Victory"),
	Diplomatic UMETA(DisplayName = "Diplomatic Victory"),
	None UMETA(DisplayName = "No Winner"),
	MAX UMETA(Hidden)
};

/**
 * Terrain types
 */
UENUM(BlueprintType)
enum class ETerrainType : uint8 {
	Land UMETA(DisplayName = "Land"),
	Water UMETA(DisplayName = "Water"),
	Mountain UMETA(DisplayName = "Mountain"),
	Desert UMETA(DisplayName = "Desert"),
	Forest UMETA(DisplayName = "Forest"),
	MAX UMETA(Hidden)
};

/**
 * AI strategies
 */
UENUM(BlueprintType)
enum class EAIStrategy : uint8 {
	Aggressive UMETA(DisplayName = "Aggressive"),
	Defensive UMETA(DisplayName = "Defensive"),
	Balanced UMETA(DisplayName = "Balanced"),
	Economic UMETA(DisplayName = "Economic"),
	Diplomatic UMETA(DisplayName = "Diplomatic"),
	MAX UMETA(Hidden)
};

// =============================================
// Structures
// =============================================

/**
 * Unit statistics
 */
USTRUCT(BlueprintType)
struct FUnitStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost = 0;  // IPC cost

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack = 0;  // Attack value

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Defense = 0;  // Defense value

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Movement = 0;  // Movement range

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health = 1;  // Hit points

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanDefend = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNaval = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAir = false;
};

/**
 * Territory data
 */
USTRUCT(BlueprintType)
struct FTerritoryData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TerritoryID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TerritoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENationID Owner = ENationID::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProductionValue = 0;  // IPC income

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETerrainType TerrainType = ETerrainType::Land;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefenseBonus = 0;  // Terrain defense

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AdjacentTerritories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCapital = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasFactory = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasShipyard = false;
};

/**
 * Unit instance data
 */
USTRUCT(BlueprintType)
struct FUnitData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 UnitID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitType UnitType = EUnitType::Infantry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENationID Owner = ENationID::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentTerritory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHealth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMovedThisTurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasAttackedThisTurn = false;
};

/**
 * Combat result
 */
USTRUCT(BlueprintType)
struct FCombatResult {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackerCasualties = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefenderCasualties = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttackerVictory = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattleLog;
};

/**
 * Player statistics
 */
USTRUCT(BlueprintType)
struct FPlayerStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENationID Nation = ENationID::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TerritoryCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalIncome = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentResources = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MilitaryStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TurnsPlayed = 0;
};

/**
 * Game configuration
 */
USTRUCT(BlueprintType)
struct FGameConfig {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameDifficulty Difficulty = EGameDifficulty::Medium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxTurns = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoResolveCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAnimateUnits = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowHints = true;
};

// =============================================
// Delegates
// =============================================

/**
 * Delegate for phase changes
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPhaseChanged, EGamePhase, int32);

/**
 * Delegate for territory ownership changes
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTerritoryOwnershipChanged, int32, ENationID, ENationID);

/**
 * Delegate for unit creation/destruction
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnitStatusChanged, uint32, EUnitType, ENationID);

/**
 * Delegate for game state changes
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameStateChanged, EGameState, EGameState);

/**
 * Delegate for combat resolution
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCombatResolved, int32, FCombatResult);
