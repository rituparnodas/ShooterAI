// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetFocalPointByActor.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_SetFocalPointByActor : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_SetFocalPointByActor();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector EnemyTargetKey;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
