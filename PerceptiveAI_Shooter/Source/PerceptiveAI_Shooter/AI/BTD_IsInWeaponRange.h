// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsInWeaponRange.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTD_IsInWeaponRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UBTD_IsInWeaponRange();

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
