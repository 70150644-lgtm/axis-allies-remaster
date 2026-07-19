#pragma once

#include "CoreMinimal.h"
#include "AAUnit.h"
#include "AATank.generated.h"

/**
 * Tank Unit - Heavy armor combat unit
 * Cost: 5 IPC | Attack: 3 | Defense: 3 | Movement: 2
 */
UCLASS()
class AXISALLIES_API AAATank : public AAAUnit {
	GENERATED_BODY()

public:
	AAATank();

	virtual void BeginPlay() override;

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const override { return TEXT("Tank"); }

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const override;

	/**
	 * Tank has armor piercing ability
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool HasArmorPiercing() const { return true; }

protected:
	virtual void InitializeUnitStats() override;
};