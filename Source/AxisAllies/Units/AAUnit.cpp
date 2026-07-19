#include "Units/AAUnit.h"
#include "Core/AAGameState.h"
#include "Kismet/GameplayStatics.h"

AAAUnit::AAAUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	bReplicates = true;

	// Generate unique unit ID
	static uint32 UnitIDCounter = 0;
	UnitID = ++UnitIDCounter;

	CurrentHealth = 1;
	bHasMovedThisTurn = false;
	bHasAttackedThisTurn = false;
	bIsInCombat = false;
}

void AAAUnit::BeginPlay()
{
	Super::BeginPlay();

	InitializeUnitStats();
	SetupUnitVisuals();
	RegisterWithGameSystems();

	CurrentHealth = UnitStats.Health;

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s created (ID: %d)"), *GetUnitName(), UnitID);
}

void AAAUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Unit tick logic can be added here
}

void AAAUnit::SetCurrentTerritory(AAATerritory* NewTerritory)
{
	if (CurrentTerritory == NewTerritory)
	{
		return;
	}

	AAATerritory* OldTerritory = CurrentTerritory;
	CurrentTerritory = NewTerritory;

	// Broadcast unit moved
	OnUnitMoved.Broadcast(OldTerritory, NewTerritory);

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s moved to new territory"), *GetUnitName());
}

int32 AAAUnit::GetTerritoryID() const
{
	return CurrentTerritory ? CurrentTerritory->GetTerritoryID() : -1;
}

bool AAAUnit::MoveToTerritory(AAATerritory* TargetTerritory)
{
	if (!TargetTerritory)
	{
		return false;
	}

	if (!CanMoveThisTurn())
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAUnit: Cannot move - already moved this turn"));
		return false;
	}

	SetCurrentTerritory(TargetTerritory);
	bHasMovedThisTurn = true;

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s moved to territory"), *GetUnitName());
	return true;
}

void AAAUnit::GetAdjacentTerritories(TArray<AAATerritory*>& OutTerritories) const
{
	OutTerritories.Empty();

	if (CurrentTerritory)
	{
		// TODO: Get adjacent territories from current territory
	}
}

bool AAAUnit::AttackTerritory(AAATerritory* TargetTerritory)
{
	if (!TargetTerritory)
	{
		return false;
	}

	if (!CanAttack())
	{
		UE_LOG(LogTemp, Warning, TEXT("AAAUnit: Cannot attack - already attacked or cannot attack this turn"));
		return false;
	}

	bHasAttackedThisTurn = true;
	bIsInCombat = true;

	// Broadcast unit attacked
	OnUnitAttacked.Broadcast(this, TargetTerritory);

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s attacked territory"), *GetUnitName());
	return true;
}

void AAAUnit::TakeDamage(int32 Damage)
{
	if (Damage <= 0)
	{
		return;
	}

	int32 OldHealth = CurrentHealth;
	CurrentHealth = FMath::Max(0, CurrentHealth - Damage);

	// Broadcast health changed
	OnHealthChanged.Broadcast(OldHealth, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s took %d damage (Health: %d -> %d)"), 
		*GetUnitName(), Damage, OldHealth, CurrentHealth);

	if (CurrentHealth <= 0)
	{
		DestroyUnit();
	}
}

void AAAUnit::Heal(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	int32 OldHealth = CurrentHealth;
	CurrentHealth = FMath::Min(UnitStats.Health, CurrentHealth + Amount);

	// Broadcast health changed
	OnHealthChanged.Broadcast(OldHealth, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s healed %d (Health: %d -> %d)"), 
		*GetUnitName(), Amount, OldHealth, CurrentHealth);
}

void AAAUnit::DestroyUnit()
{
	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s destroyed"), *GetUnitName());

	// Broadcast unit destroyed
	OnUnitDestroyed.Broadcast();

	// Unregister from game state
	AAGameState* GameState = GetWorld()->GetGameState<AAGameState>();
	if (GameState)
	{
		GameState->UnregisterUnit(this);
	}

	// Destroy actor
	Destroy();
}

void AAAUnit::ResetTurn()
{
	bHasMovedThisTurn = false;
	bHasAttackedThisTurn = false;
	bIsInCombat = false;

	UE_LOG(LogTemp, Warning, TEXT("AAAUnit: %s reset for new turn"), *GetUnitName());
}

float AAAUnit::GetHealthPercentage() const
{
	if (UnitStats.Health <= 0)
	{
		return 0.0f;
	}

	return (float)CurrentHealth / UnitStats.Health;
}

FString AAAUnit::GetUnitDescription() const
{
	return FString::Printf(TEXT("%s - Attack: %d, Defense: %d, Movement: %d"),
		*GetUnitName(),
		UnitStats.Attack,
		UnitStats.Defense,
		UnitStats.Movement);
}

bool AAAUnit::IsGroundUnit() const
{
	return !UnitStats.bIsAir && !UnitStats.bIsNaval;
}

class UTexture2D* AAAUnit::GetUnitIcon() const
{
	// TODO: Return unit icon texture
	return nullptr;
}

void AAAUnit::InitializeUnitStats()
{
	// Base implementation - should be overridden by subclasses
	UnitStats.Cost = 1;
	UnitStats.Attack = 1;
	UnitStats.Defense = 1;
	UnitStats.Movement = 1;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
}

void AAAUnit::SetupUnitVisuals()
{
	// TODO: Setup unit mesh and materials based on type
}

void AAAUnit::RegisterWithGameSystems()
{
	AAGameState* GameState = GetWorld()->GetGameState<AAGameState>();
	if (GameState)
	{
		GameState->RegisterUnit(this);
	}
}
