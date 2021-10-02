// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation\PathFollowingComponent.h"
#include "AIModule\Classes\AITypes.h"
#include "BTT_MoveAlongPatrolPath.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_MoveAlongPatrolPath : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_MoveAlongPatrolPath();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;
	class APatrolRoute* PatrolRoute = nullptr;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
