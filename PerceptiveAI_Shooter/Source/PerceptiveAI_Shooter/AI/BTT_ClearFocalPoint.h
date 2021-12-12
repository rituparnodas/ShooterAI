// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ClearFocalPoint.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_ClearFocalPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_ClearFocalPoint();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
