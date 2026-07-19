#pragma once

#include "CoreMinimal.h"
#include "AAUnit.h"
#include "AAFighter.generated.h"

/**
 * Fighter Plane Unit - Air superiority combat unit
 * Cost: 10 IPC | Attack: 3 | Defense: 3 | Movement: 4
 */
UCLASS()
class AXISALLIES_API AAAFighter : public AAAUnit {
	GENERATED_BODY()

public:
	AAAFighter();

	virtual void BeginPlay() override;

	/**
	 * Get unit name
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitName() const override { return TEXT("Fighter"); }

	/**
	 * Get unit description
	 */
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual FString GetUnitDescription() const override;

	/**
	 * Can provide air cover to friendly units in territory
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanProvideAirCover() const { return true; }

	/**
	 * Get air defense bonus
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetAirDefenseBonus() const { return 1; }

protected:
	virtual void InitializeUnitStats() override;
};