#include "Units/AAMechanizedVehicle.h\"

AAAMechanizedVehicle::AAAMechanizedVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	UnitType = EUnitType::Armor;
}

void AAAMechanizedVehicle::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AAAMechanizedVehicle: Created"));
}

FString AAAMechanizedVehicle::GetUnitDescription() const
{
	return TEXT("Mechanized Vehicle - Fast transport unit. Cost: 5 IPC. Attack: 1, Defense: 2, Movement: 2");
}

void AAAMechanizedVehicle::InitializeUnitStats()
{
	UnitStats.Cost = 5;
	UnitStats.Attack = 1;
	UnitStats.Defense = 2;
	UnitStats.Movement = 2;
	UnitStats.Health = 1;
	UnitStats.bCanAttack = true;
	UnitStats.bCanDefend = true;
	UnitStats.bIsAir = false;
	UnitStats.bIsNaval = false;
}
