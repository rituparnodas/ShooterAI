// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetAimingMode.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_SetAimingMode : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_SetAimingMode();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BTTasks")
		bool IsAiming;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
