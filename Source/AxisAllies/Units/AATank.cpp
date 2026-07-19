#include "Units/AATank.h"

AAATank::AAATank()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitType = EUnitType::Armor;
}

void AAATank::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AAATank: Created"));
}

FString AAATank::GetUnitDescription() const
{
	return TEXT("Tank - Heavy armor combat unit. Cost: 5 IPC. Attack: 3, Defense: 3, Movement: 2. Has armor piercing ability.");
}

void AAATank::InitializeUnitStats()
{
	UnitStats.Cost = 5;
	UnitStats.Attack = 3;
	UnitStats.Defense = 3;
	UnitStats.Movement = 2;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
	UnitStats.bIsAir = false;
	UnitStats.bIsNaval = false;
}
