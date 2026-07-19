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
 * Unit statistics
 */
USTRUCT(BlueprintType)
struct FUnitStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Defense = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Movement = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health = 1;

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
	int32 ProductionValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AdjacentTerritories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCapital = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasFactory = false;
};

/**
 * Delegate for phase changes
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPhaseChanged, EGamePhase, int32);

/**
 * Delegate for territory ownership changes
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTerritoryOwnershipChanged, int32, ENationID, ENationID);