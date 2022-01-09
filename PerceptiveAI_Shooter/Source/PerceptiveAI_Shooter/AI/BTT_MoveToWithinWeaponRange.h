// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation\PathFollowingComponent.h"
#include "AIModule\Classes\AITypes.h"
#include "BTT_MoveToWithinWeaponRange.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_MoveToWithinWeaponRange : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_MoveToWithinWeaponRange();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector EnemyTargetKey;

	UFUNCTION()
		void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};