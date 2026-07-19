#include "Core/AAGameState.h"
#include "Units/AAUnit.h"
#include "Net/UnrealNetwork.h"

AAGameState::AAGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;

	bReplicates = true;

	TurnNumber = 0;
	CurrentPlayerIndex = 0;
}

void AAGameState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AAGameState: Initialized"));
}

void AAGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Periodic updates can be added here
}

AAANation* AAGameState::GetNation(ENationID NationID) const
{
	for (AAANation* Nation : Nations)
	{
		if (Nation && Nation->GetNationID() == NationID)
		{
			return Nation;
		}
	}
	return nullptr;
}

AAANation* AAGameState::GetCurrentPlayerNation() const
{
	if (Nations.IsValidIndex(CurrentPlayerIndex))
	{
		return Nations[CurrentPlayerIndex];
	}
	return nullptr;
}

void AAGameState::AddNation(AAANation* NewNation)
{
	if (NewNation)
	{
		Nations.Add(NewNation);
		NationResources.Add(NewNation->GetNationID(), 0);
		UE_LOG(LogTemp, Warning, TEXT("AAGameState: Nation added - %d total nations"), Nations.Num());
	}
}

void AAGameState::RemoveNation(ENationID NationID)
{
	for (int32 i = 0; i < Nations.Num(); ++i)
	{
		if (Nations[i] && Nations[i]->GetNationID() == NationID)
		{
			Nations.RemoveAt(i);
			NationResources.Remove(NationID);
			UE_LOG(LogTemp, Warning, TEXT("AAGameState: Nation removed"));
			break;
		}
	}
}

int32 AAGameState::GetNationResources(ENationID NationID) const
{
	const int32* ResourcePtr = NationResources.Find(NationID);
	return ResourcePtr ? *ResourcePtr : 0;
}

void AAGameState::AddNationResources(ENationID NationID, int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	int32* ResourcePtr = NationResources.Find(NationID);
	if (ResourcePtr)
	{
		*ResourcePtr += Amount;
		UE_LOG(LogTemp, Warning, TEXT("AAGameState: Added %d resources to nation"), Amount);
	}
	else
	{
		NationResources.Add(NationID, Amount);
	}
}

bool AAGameState::SubtractNationResources(ENationID NationID, int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	int32* ResourcePtr = NationResources.Find(NationID);
	if (!ResourcePtr || *ResourcePtr < Amount)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAGameState: Insufficient resources"));
		return false;
	}

	*ResourcePtr -= Amount;
	UE_LOG(LogTemp, Warning, TEXT("AAGameState: Subtracted %d resources from nation"), Amount);
	return true;
}

int32 AAGameState::GetNationTerritoryCount(ENationID NationID) const
{
	// TODO: Iterate through game board territories and count owned by this nation
	return 0;
}

int32 AAGameState::GetNationIncome(ENationID NationID) const
{
	// TODO: Calculate income based on controlled territories
	return GetNationTerritoryCount(NationID);  // 1 IPC per territory
}

void AAGameState::TransferTerritoryOwnership(int32 TerritoryID, ENationID NewOwner)
{
	// TODO: Update territory ownership on game board
	UE_LOG(LogTemp, Warning, TEXT("AAGameState: Territory %d transferred to nation"), TerritoryID);
}

int32 AAGameState::GetNationUnitCount(ENationID NationID) const
{
	const TArray<AAAUnit*>* UnitsPtr = NationUnits.Find(NationID);
	return UnitsPtr ? UnitsPtr->Num() : 0;
}

int32 AAGameState::GetNationUnitCountByType(ENationID NationID, EUnitType UnitType) const
{
	const TArray<AAAUnit*>* UnitsPtr = NationUnits.Find(NationID);
	if (!UnitsPtr)
	{
		return 0;
	}

	int32 Count = 0;
	for (AAAUnit* Unit : *UnitsPtr)
	{
		if (Unit && Unit->GetUnitType() == UnitType)
		{
			Count++;
		}
	}
	return Count;
}

void AAGameState::RegisterUnit(AAAUnit* Unit)
{
	if (!Unit)
	{
		return;
	}

	ENationID Owner = Unit->GetOwnerNation();
	uint32 UnitID = Unit->GetUnitID();

	AllUnits.Add(UnitID, Unit);

	if (!NationUnits.Contains(Owner))
	{
		NationUnits.Add(Owner, TArray<AAAUnit*>());
	}
	NationUnits[Owner].Add(Unit);

	UE_LOG(LogTemp, Warning, TEXT("AAGameState: Unit registered - Total units: %d"), AllUnits.Num());
}

void AAGameState::UnregisterUnit(AAAUnit* Unit)
{
	if (!Unit)
	{
		return;
	}

	ENationID Owner = Unit->GetOwnerNation();
	uint32 UnitID = Unit->GetUnitID();

	AllUnits.Remove(UnitID);

	if (NationUnits.Contains(Owner))
	{
		NationUnits[Owner].RemoveSingle(Unit);
	}

	UE_LOG(LogTemp, Warning, TEXT("AAGameState: Unit unregistered - Total units: %d"), AllUnits.Num());
}

void AAGameState::GetUnitsInTerritory(int32 TerritoryID, TArray<AAAUnit*>& OutUnits) const
{
	const TArray<AAAUnit*>* UnitsPtr = TerritoryUnits.Find(TerritoryID);
	if (UnitsPtr)
	{
		OutUnits = *UnitsPtr;
	}
}

FPlayerStats AAGameState::GetNationStats(ENationID NationID) const
{
	FPlayerStats Stats;
	Stats.Nation = NationID;
	Stats.TerritoryCount = GetNationTerritoryCount(NationID);
	Stats.UnitCount = GetNationUnitCount(NationID);
	Stats.TotalIncome = GetNationIncome(NationID);
	Stats.CurrentResources = GetNationResources(NationID);
	Stats.MilitaryStrength = GetNationMilitaryStrength(NationID);
	Stats.TurnsPlayed = TurnNumber;

	return Stats;
}

float AAGameState::GetNationMilitaryStrength(ENationID NationID) const
{
	return CalculateMilitaryStrength(NationID);
}

TMap<ENationID, FPlayerStats> AAGameState::GetAllStats() const
{
	TMap<ENationID, FPlayerStats> AllStats;

	TArray<ENationID> Nations = { ENationID::Germany, ENationID::Japan, ENationID::Italy, 
		ENationID::SovietUnion, ENationID::UnitedStates, ENationID::UnitedKingdom };

	for (ENationID Nation : Nations)
	{
		AllStats.Add(Nation, GetNationStats(Nation));
	}

	return AllStats;
}

void AAGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAGameState, Nations);
	DOREPLIFETIME(AAGameState, TurnNumber);
	DOREPLIFETIME(AAGameState, CurrentPlayerIndex);
	DOREPLIFETIME(AAGameState, NationResources);
}

void AAGameState::UpdateMilitaryStrength(ENationID NationID)
{
	// TODO: Recalculate military strength based on current units
}

float AAGameState::CalculateMilitaryStrength(ENationID NationID) const
{
	float Strength = 0.0f;

	const TArray<AAAUnit*>* UnitsPtr = NationUnits.Find(NationID);
	if (!UnitsPtr)
	{
		return Strength;
	}

	for (AAAUnit* Unit : *UnitsPtr)
	{
		if (Unit)
		{
			// Add attack and defense power
			Strength += Unit->GetAttackPower();
			Strength += Unit->GetDefensePower();
		}
	}

	return Strength;
}
