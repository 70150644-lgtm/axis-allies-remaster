#include "Units/AAFighter.h"

AAAFighter::AAAFighter()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitType = EUnitType::Fighter;
}

void AAAFighter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AAAFighter: Created"));
}

FString AAAFighter::GetUnitDescription() const
{
	return TEXT("Fighter - Air superiority combat unit. Cost: 10 IPC. Attack: 3, Defense: 3, Movement: 4. Can provide air cover.");
}

void AAAFighter::InitializeUnitStats()
{
	UnitStats.Cost = 10;
	UnitStats.Attack = 3;
	UnitStats.Defense = 3;
	UnitStats.Movement = 4;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
	UnitStats.bIsAir = true;
	UnitStats.bIsNaval = false;
}
