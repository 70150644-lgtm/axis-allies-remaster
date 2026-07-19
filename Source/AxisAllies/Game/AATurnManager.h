#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AATypes.h"
#include "AATurnManager.generated.h"

class AAAGameMode;

/**
 * Manages turn progression and phase transitions
 */
UCLASS()
class AXISALLIES_API AATurnManager : public AActor {
	GENERATED_BODY()

public:
	AATurnManager();

	virtual void BeginPlay() override;

	// =============================================
	// Turn Management
	// =============================================

	/**
	 * Initialize turn system
	 */
	void Initialize(class AAAGameMode* InGameMode);

	/**
	 * Start a new turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void StartNewTurn();

	/**
	 * Progress to next phase
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void NextPhase();

	/**
	 * Skip current phase
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void SkipPhase();

	/**
	 * End turn
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	void EndTurn();

	// =============================================
	// Turn State Accessors
	// =============================================

	/**
	 * Get current turn number
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	int32 GetTurnNumber() const { return TurnNumber; }

	/**
	 * Get current player index
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	int32 GetCurrentPlayerIndex() const { return CurrentPlayerIndex; }

	/**
	 * Get current phase
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	EGamePhase GetCurrentPhase() const { return CurrentPhase; }

	/**
	 * Get time remaining in turn (for turn timer)
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	float GetTimeRemainingInTurn() const;

	/**
	 * Get phase time remaining
	 */
	UFUNCTION(BlueprintCallable, Category = "Turn")
	float GetPhaseTimeRemaining() const;

	// =============================================
	// Delegates
	// =============================================

	/**
	 * Called when turn starts
	 */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTurnStarted, int32);
	FOnTurnStarted OnTurnStarted;

	/**
	 * Called when phase changes
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPhaseChanged, EGamePhase, EGamePhase);
	FOnPhaseChanged OnPhaseChanged;

	/**
	 * Called when turn ends
	 */
	DECLARE_MULTICAST_DELEGATE(FOnTurnEnded);
	FOnTurnEnded OnTurnEnded;

	/**
	 * Called when time runs out in phase
	 */
	DECLARE_MULTICAST_DELEGATE(FOnPhaseTimeExpired);
	FOnPhaseTimeExpired OnPhaseTimeExpired;

protected:
	// =============================================
	// Turn State
	// =============================================

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	int32 TurnNumber;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	int32 CurrentPlayerIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	EGamePhase CurrentPhase;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	EGamePhase NextPhaseInSequence;

	// =============================================
	// Timing
	// =============================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn")
	float TurnTimeLimit = 300.0f;  // 5 minutes per turn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn")
	float PhaseTimeLimit = 60.0f;  // 1 minute per phase

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	float TurnStartTime;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	float PhaseStartTime;

	bool bTimerActive;

	// =============================================
	// References
	// =============================================

	UPROPERTY()
	class AAAGameMode* GameModeRef;

	UPROPERTY()
	class AAGameState* GameStateRef;

	// =============================================
	// Phase Sequence
	// =============================================

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	TArray<EGamePhase> PhaseSequence;

	UPROPERTY(BlueprintReadOnly, Category = "Turn")
	int32 CurrentPhaseIndex;

	// =============================================
	// Protected Methods
	// =============================================

	virtual void Tick(float DeltaTime) override;

	/**
	 * Initialize phase sequence
	 */
	void InitializePhaseSequence();

	/**
	 * Get next phase in sequence
	 */
	EGamePhase GetNextPhase() const;

	/**
	 * Update turn timer
	 */
	void UpdateTurnTimer(float DeltaTime);

	/**
	 * Check if phase time expired
	 */
	void CheckPhaseTimeExpired();

	/**
	 * Advance to next player
	 */
	void AdvanceToNextPlayer();

	/**
	 * Execute phase-specific logic
	 */
	void ExecutePhase(EGamePhase Phase);
};