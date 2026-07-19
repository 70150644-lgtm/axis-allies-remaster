#include "Units/AABomber.h"

AABomber::AABomber()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitType = EUnitType::Bomber;
}

void AABomber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AABomber: Created"));
}

FString AABomber::GetUnitDescription() const
{
	return TEXT("Bomber - Long-range bombing unit. Cost: 12 IPC. Attack: 4, Defense: 1, Movement: 5. Can bomb industrial targets.");
}

void AABomber::InitializeUnitStats()
{
	UnitStats.Cost = 12;
	UnitStats.Attack = 4;
	UnitStats.Defense = 1;
	UnitStats.Movement = 5;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
	UnitStats.bIsAir = true;
	UnitStats.bIsNaval = false;
}
