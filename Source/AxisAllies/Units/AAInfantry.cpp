#include "Units/AAInfantry.h"

AAAInfantry::AAAInfantry()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitType = EUnitType::Infantry;
}

void AAAInfantry::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AAAInfantry: Created"));
}

FString AAAInfantry::GetUnitDescription() const
{
	return TEXT("Infantry - Basic ground unit. Cost: 3 IPC. Attack: 1, Defense: 2, Movement: 1");
}

void AAAInfantry::InitializeUnitStats()
{
	UnitStats.Cost = 3;
	UnitStats.Attack = 1;
	UnitStats.Defense = 2;
	UnitStats.Movement = 1;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
	UnitStats.bIsAir = false;
	UnitStats.bIsNaval = false;
}
