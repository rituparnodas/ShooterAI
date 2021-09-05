// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_UpdateMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_UpdateMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

		UBTT_UpdateMovementSpeed();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BTTasks")
		FBlackboardKeySelector StateKey;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
