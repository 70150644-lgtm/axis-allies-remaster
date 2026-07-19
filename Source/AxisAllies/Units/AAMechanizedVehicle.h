#pragma once

#include "CoreMinimal.h"
#include "AAUnit.h"
#include "AAMechanizedVehicle.generated.h"

/**
 * Mechanized Vehicle Unit - Fast transport unit
 * Cost: 5 IPC | Attack: 1 | Defense: 2 | Movement: 2
 */
UCLASS()
class AXISALLIES_API AAAMechanizedVehicle : public AAAUnit {
	GENERATED_BODY()

public:
	AAAMechanizedVehicle();

	virtual void BeginPlay() override;

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const override { return TEXT("Mechanized Vehicle"); }

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const override;

protected:
	virtual void InitializeUnitStats() override;
};