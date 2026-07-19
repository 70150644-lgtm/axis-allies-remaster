#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AATypes.h"
#include "AAGameMode.generated.h"

class AAGameState;
class AATurnManager;
class AACombatSystem;
class AAEconomySystem;
class AAGameBoard;

/**
 * Main WWII RTS Game Mode
 * Handles turn-based gameplay, game flow, and rule enforcement
 */
UCLASS()
class AXISALLIES_API AAAGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	AAAGameMode();

	// =============================================
	// Game Initialization
	// =============================================

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	// =============================================
	// Game State Management
	// =============================================

	/**
	 * Initialize the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void InitializeGame(const FGameConfig& InGameConfig);

	/**
	 * Start the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	/**
	 * Pause/Resume the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame(bool bPause);

	/**
	 * End the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame(EVictoryCondition VictoryType, ENationID Winner);

	// =============================================
	// Turn Management
	// =============================================

	/**
	 * Advance to next turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void NextTurn();

	/**
	 * Advance to next phase
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void NextPhase();

	/**
	 * Get current turn number
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	int32 GetCurrentTurn() const { return CurrentTurnNumber; }

	/**
	 * Get current player index
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	int32 GetCurrentPlayerIndex() const { return CurrentPlayerIndex; }

	/**
	 * Get current game phase
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	EGamePhase GetCurrentPhase() const { return CurrentPhase; }

	// =============================================
	// Game Rules & Validation
	// =============================================

	/**
	 * Validate unit movement
	 */
	UFUNCTION(BlueprintCallable, Category = "Rules")
	bool IsValidUnitMovement(class AAAUnit* Unit, int32 TargetTerritoryID) const;

	/**
	 * Validate attack
	 */
	UFUNCTION(BlueprintCallable, Category = "Rules")
	bool IsValidAttack(class AAAUnit* Attacker, int32 TargetTerritoryID) const;

	/**
	 * Validate unit purchase
	 */
	UFUNCTION(BlueprintCallable, Category = "Rules")
	bool CanPurchaseUnit(ENationID Nation, EUnitType UnitType) const;

	/**
	 * Check victory condition
	 */
	UFUNCTION(BlueprintCallable, Category = "Rules")
	bool CheckVictoryCondition(ENationID& OutWinner, EVictoryCondition& OutVictoryType);

	// =============================================
	// System Accessors
	// =============================================

	UFUNCTION(BlueprintCallable, Category = "Systems")
	AAGameState* GetGameStateRef() const { return GameStateRef; }

	UFUNCTION(BlueprintCallable, Category = "Systems")
	AATurnManager* GetTurnManager() const { return TurnManagerRef; }

	UFUNCTION(BlueprintCallable, Category = "Systems")
	AACombatSystem* GetCombatSystem() const { return CombatSystemRef; }

	UFUNCTION(BlueprintCallable, Category = "Systems")
	AAEconomySystem* GetEconomySystem() const { return EconomySystemRef; }

	UFUNCTION(BlueprintCallable, Category = "Systems")
	AAGameBoard* GetGameBoard() const { return GameBoardRef; }

	// =============================================
	// Event Callbacks
	// =============================================

	/**
	 * Called when phase changes
	 */
	FOnPhaseChanged OnPhaseChanged;

	/**
	 * Called when game state changes
	 */
	FOnGameStateChanged OnGameStateChanged;

	/**
	 * Called when territory ownership changes
	 */
	FOnTerritoryOwnershipChanged OnTerritoryOwnershipChanged;

protected:
	// =============================================
	// Game Systems
	// =============================================

	UPROPERTY()
	class AAGameState* GameStateRef;

	UPROPERTY()
	class AATurnManager* TurnManagerRef;

	UPROPERTY()
	class AACombatSystem* CombatSystemRef;

	UPROPERTY()
	class AAEconomySystem* EconomySystemRef;

	UPROPERTY()
	class AAGameBoard* GameBoardRef;

	// =============================================
	// Game State
	// =============================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FGameConfig CurrentGameConfig;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	EGameState CurrentGameState;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	EGamePhase CurrentPhase;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentTurnNumber;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentPlayerIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	bool bGamePaused;

	// =============================================
	// Protected Methods
	// =============================================

	/**
	 * Create and initialize game systems
	 */
	void CreateGameSystems();

	/**
	 * Setup initial board and territories
	 */
	void SetupInitialBoard();

	/**
	 * Spawn AI players
	 */
	void SpawnAIPlayers();

	/**
	 * Transition to next phase
	 */
	void TransitionPhase(EGamePhase NewPhase);

	/**
	 * Execute phase logic
	 */
	void ExecutePhaseLogic(EGamePhase Phase);

	/**
	 * Collect income for current player
	 */
	void CollectIncome();

	/**
	 * Process end of turn
	 */
	void ProcessEndOfTurn();

	/**
	 * Check for game end conditions
	 */
	void CheckGameEndConditions();
};