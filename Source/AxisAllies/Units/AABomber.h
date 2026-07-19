#pragma once

#include "CoreMinimal.h"
#include "AAUnit.h"
#include "AABomber.generated.h"

/**
 * Bomber Plane Unit - Long-range bombing unit
 * Cost: 12 IPC | Attack: 4 | Defense: 1 | Movement: 5
 */
UCLASS()
class AXISALLIES_API AABomber : public AAAUnit {
	GENERATED_BODY()

public:
	AABomber();

	virtual void BeginPlay() override;

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const override { return TEXT("Bomber"); }

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const override;

	/**
	 * Bombers deal extra damage to non-fighter units
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetBombardmentBonus() const { return 2; }

	/**
	 * Can bomb industrial targets (factories, shipyards)
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanBombIndustrial() const { return true; }

	/**
	 * Can conduct strategic bombing
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanStrategicBomb() const { return true; }

protected:
	virtual void InitializeUnitStats() override;
};