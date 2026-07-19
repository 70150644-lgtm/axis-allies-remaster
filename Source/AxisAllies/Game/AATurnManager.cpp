#include "Game/AATurnManager.h"
#include "Game/AAGameMode.h"
#include "Core/AAGameState.h"
#include "Kismet/GameplayStatics.h"

AATurnManager::AATurnManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	TurnNumber = 0;
	CurrentPlayerIndex = 0;
	CurrentPhase = EGamePhase::Purchase;
	CurrentPhaseIndex = 0;
	bTimerActive = true;
	TurnStartTime = 0.0f;
	PhaseStartTime = 0.0f;
}

void AATurnManager::BeginPlay()
{
	Super::BeginPlay();

	GameStateRef = GetWorld()->GetGameState<AAGameState>();
	InitializePhaseSequence();

	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Initialized"));
}

void AATurnManager::Initialize(AAAGameMode* InGameMode)
{
	GameModeRef = InGameMode;
	GameStateRef = GetWorld()->GetGameState<AAGameState>();

	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Initialized with GameMode"));
}

void AATurnManager::StartNewTurn()
{
	TurnNumber++;
	CurrentPhaseIndex = 0;
	CurrentPhase = PhaseSequence[0];

	TurnStartTime = GetWorld()->GetTimeSeconds();
	PhaseStartTime = TurnStartTime;

	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: New turn started - Turn %d, Player %d, Phase: %d"), 
		TurnNumber, CurrentPlayerIndex, (int32)CurrentPhase);

	// Broadcast turn started
	OnTurnStarted.Broadcast(TurnNumber);

	// Execute purchase phase
	ExecutePhase(CurrentPhase);
}

void AATurnManager::NextPhase()
{
	if (CurrentPhaseIndex < PhaseSequence.Num() - 1)
	{
		EGamePhase OldPhase = CurrentPhase;
		CurrentPhaseIndex++;
		CurrentPhase = PhaseSequence[CurrentPhaseIndex];

		PhaseStartTime = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Advanced to phase %d"), (int32)CurrentPhase);

		// Broadcast phase changed
		OnPhaseChanged.Broadcast(OldPhase, CurrentPhase);

		// Execute new phase
		ExecutePhase(CurrentPhase);
	}
	else
	{
		EndTurn();
	}
}

void AATurnManager::SkipPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Skipping current phase"));
	NextPhase();
}

void AATurnManager::EndTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Turn ended"));

	// Advance to next player
	AdvanceToNextPlayer();

	// Broadcast turn ended
	OnTurnEnded.Broadcast();

	// Start next turn
	StartNewTurn();
}

float AATurnManager::GetTimeRemainingInTurn() const
{
	float Elapsed = GetWorld()->GetTimeSeconds() - TurnStartTime;
	float Remaining = FMath::Max(0.0f, TurnTimeLimit - Elapsed);
	return Remaining;
}

float AATurnManager::GetPhaseTimeRemaining() const
{
	float Elapsed = GetWorld()->GetTimeSeconds() - PhaseStartTime;
	float Remaining = FMath::Max(0.0f, PhaseTimeLimit - Elapsed);
	return Remaining;
}

void AATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimerActive)
	{
		UpdateTurnTimer(DeltaTime);
		CheckPhaseTimeExpired();
	}
}

void AATurnManager::InitializePhaseSequence()
{
	PhaseSequence.Empty();
	PhaseSequence.Add(EGamePhase::Purchase);
	PhaseSequence.Add(EGamePhase::Deploy);
	PhaseSequence.Add(EGamePhase::Combat);
	PhaseSequence.Add(EGamePhase::Movement);
	PhaseSequence.Add(EGamePhase::EndTurn);

	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Phase sequence initialized with %d phases"), PhaseSequence.Num());
}

EGamePhase AATurnManager::GetNextPhase() const
{
	if (CurrentPhaseIndex < PhaseSequence.Num() - 1)
	{
		return PhaseSequence[CurrentPhaseIndex + 1];
	}
	return PhaseSequence[0];
}

void AATurnManager::UpdateTurnTimer(float DeltaTime)
{
	float TimeRemaining = GetTimeRemainingInTurn();

	if (TimeRemaining <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Turn time limit exceeded"));
		EndTurn();
	}
}

void AATurnManager::CheckPhaseTimeExpired()
{
	float PhaseTimeRemaining = GetPhaseTimeRemaining();

	if (PhaseTimeRemaining <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Phase time limit exceeded"));
		OnPhaseTimeExpired.Broadcast();
		NextPhase();
	}
}

void AATurnManager::AdvanceToNextPlayer()
{
	// Assuming 6 playable nations
	CurrentPlayerIndex = (CurrentPlayerIndex + 1) % 6;

	UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Advanced to player %d"), CurrentPlayerIndex);
}

void AATurnManager::ExecutePhase(EGamePhase Phase)
{
	switch (Phase)
	{
		case EGamePhase::Purchase:
			UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Executing PURCHASE phase"));
			// TODO: Allow unit purchases
			break;

		case EGamePhase::Deploy:
			UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Executing DEPLOY phase"));
			// TODO: Allow unit deployment
			break;

		case EGamePhase::Combat:
			UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Executing COMBAT phase"));
			// TODO: Allow combat actions
			break;

		case EGamePhase::Movement:
			UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Executing MOVEMENT phase"));
			// TODO: Allow unit movement
			break;

		case EGamePhase::EndTurn:
			UE_LOG(LogTemp, Warning, TEXT("AATurnManager: Executing END TURN phase"));
			// TODO: Collect income, check victories
			break;

		default:
			break;
	}
}
