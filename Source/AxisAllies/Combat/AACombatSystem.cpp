#include "Combat/AACombatSystem.h"
#include "Combat/AACombatResolver.h"
#include "Units/AAUnit.h"

AACombatSystem::AACombatSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	bAutoResolveCombat = false;
	bAnimateCombat = true;
	CombatAnimationSpeed = 1.0f;
}

void AACombatSystem::BeginPlay()
{
	Super::BeginPlay();

	// Create combat resolver
	if (!CombatResolverRef && GetWorld())
	{
		CombatResolverRef = GetWorld()->SpawnActor<AACombatResolver>();
		if (CombatResolverRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Combat Resolver created"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Initialized"));
}

bool AACombatSystem::StartCombat(
	AAAUnit* AttackingUnit,
	class AAATerritory* DefendingTerritory)
{
	if (!AttackingUnit || !DefendingTerritory)
	{
		return false;
	}

	int32 TerritoryID = DefendingTerritory->GetTerritoryID();

	// Check if combat already active
	if (ActiveCombats.Contains(TerritoryID))
	{
		UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Combat already active in territory %d"), TerritoryID);
		return false;
	}

	// Create combat state
	FCombatState NewCombat;
	NewCombat.TerritoryID = TerritoryID;
	NewCombat.AttackingUnits.Add(AttackingUnit);
	NewCombat.RoundNumber = 1;
	NewCombat.bResolved = false;
	NewCombat.CombatLog = FString::Printf(TEXT("Combat started in territory %d\n"), TerritoryID);

	// TODO: Get defending units from territory
	// NewCombat.DefendingUnits = DefendingTerritory->GetGarrison();

	ActiveCombats.Add(TerritoryID, NewCombat);

	UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Combat started in territory %d"), TerritoryID);

	// Broadcast combat started
	OnCombatStarted.Broadcast(TerritoryID, NewCombat.AttackingUnits);

	return true;
}

FCombatResult AACombatSystem::ResolveCombat(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits,
	class AAATerritory* BattleLocation,
	bool bAutoResolve)
{
	FCombatResult Result;

	if (!CombatResolverRef)
	{
		UE_LOG(LogTemp, Error, TEXT("AACombatSystem: Combat Resolver not initialized"));
		return Result;
	}

	// Resolve combat using resolver
	Result = CombatResolverRef->ResolveCombat(AttackingUnits, DefendingUnits, BattleLocation);

	// Update active combat
	if (BattleLocation)
	{
		int32 TerritoryID = BattleLocation->GetTerritoryID();

		if (ActiveCombats.Contains(TerritoryID))
		{
			FCombatState& Combat = ActiveCombats[TerritoryID];
			Combat.bResolved = true;

			// Broadcast combat resolved
			OnCombatRoundResolved.Broadcast(TerritoryID, Result);

			// Check if combat is over
			if (AttackingUnits.Num() > 0)
			{
				EndCombat(TerritoryID, AttackingUnits[0]);
			}
		}
	}

	return Result;
}

void AACombatSystem::RetreatFromCombat(AAAUnit* AttackingUnit)
{
	if (!AttackingUnit)
	{
		return;
	}

	// TODO: Find combat containing this unit and remove it
	UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Unit retreated from combat"));
}

bool AACombatSystem::IsCombatActive(int32 TerritoryID) const
{
	return ActiveCombats.Contains(TerritoryID);
}

void AACombatSystem::GetActiveCombats(TArray<int32>& OutTerritoryIDs) const
{
	ActiveCombats.GetKeys(OutTerritoryIDs);
}

void AACombatSystem::GetCombatUnits(
	int32 TerritoryID,
	TArray<AAAUnit*>& OutAttackers,
	TArray<AAAUnit*>& OutDefenders) const
{
	const FCombatState* CombatPtr = ActiveCombats.Find(TerritoryID);
	if (CombatPtr)
	{
		OutAttackers = CombatPtr->AttackingUnits;
		OutDefenders = CombatPtr->DefendingUnits;
	}
}

void AACombatSystem::CalculateCombatOdds(
	const TArray<AAAUnit*>& AttackingUnits,
	const TArray<AAAUnit*>& DefendingUnits,
	float& OutAttackerWinProbability,
	int32& OutExpectedAttackerCasualties,
	int32& OutExpectedDefenderCasualties)
{
	if (!CombatResolverRef)
	{
		return;
	}

	CombatResolverRef->CalculateCombatOdds(AttackingUnits, DefendingUnits, OutAttackerWinProbability);
	OutExpectedAttackerCasualties = CombatResolverRef->GetExpectedCasualties(DefendingUnits, false);
	OutExpectedDefenderCasualties = CombatResolverRef->GetExpectedCasualties(AttackingUnits, true);
}

FString AACombatSystem::GetCombatLog(int32 TerritoryID) const
{
	const FCombatState* CombatPtr = ActiveCombats.Find(TerritoryID);
	if (CombatPtr)
	{
		return CombatPtr->CombatLog;
	}

	const FString* HistoryPtr = CombatHistory.Find(TerritoryID);
	return HistoryPtr ? *HistoryPtr : FString(TEXT("No combat log"));
}

void AACombatSystem::EndCombat(int32 TerritoryID, AAAUnit* Conqueror)
{
	UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Combat ended in territory %d"), TerritoryID);

	// Move combat to history
	if (ActiveCombats.Contains(TerritoryID))
	{
		FCombatState& Combat = ActiveCombats[TerritoryID];
		CombatHistory.Add(TerritoryID, Combat.CombatLog);
		ActiveCombats.Remove(TerritoryID);
	}

	// Broadcast combat ended
	if (Conqueror)
	{
		OnCombatEnded.Broadcast(TerritoryID, Conqueror);
	}
}

void AACombatSystem::RemoveCasualties(
	TArray<AAAUnit*>& Units,
	const TArray<AAAUnit*>& Casualties)
{
	for (AAAUnit* Casualty : Casualties)
	{
		Units.RemoveSingle(Casualty);
	}
}

void AACombatSystem::OccupyTerritory(AAAUnit* Conqueror, class AAATerritory* Territory)
{
	if (!Conqueror || !Territory)
	{
		return;
	}

	// TODO: Transfer territory ownership
	UE_LOG(LogTemp, Warning, TEXT("AACombatSystem: Territory occupied"));

	// Broadcast territory captured
	OnTerritoryCaptured.Broadcast(Territory->GetTerritoryID(), Conqueror, Territory);
}

void AACombatSystem::LogCombatAction(int32 TerritoryID, const FString& Action)
{
	if (ActiveCombats.Contains(TerritoryID))
	{
		FCombatState& Combat = ActiveCombats[TerritoryID];
		Combat.CombatLog += Action + TEXT("\n");
	}
}
