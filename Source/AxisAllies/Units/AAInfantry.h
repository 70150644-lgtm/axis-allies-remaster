#pragma once

#include "CoreMinimal.h"
#include "AAUnit.h"
#include "AAInfantry.generated.h"

/**
 * Infantry Unit - Basic ground unit
 * Cost: 3 IPC | Attack: 1 | Defense: 2 | Movement: 1
 */
UCLASS()
class AXISALLIES_API AAAInfantry : public AAAUnit {
	GENERATED_BODY()

public:
	AAAInfantry();

	virtual void BeginPlay() override;

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const override { return TEXT("Infantry"); }

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const override;

protected:
	virtual void InitializeUnitStats() override;
};