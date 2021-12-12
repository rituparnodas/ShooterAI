// Copyright DevDasTour 2021 All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ModifyState.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTIVEAI_SHOOTER_API UBTT_ModifyState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_ModifyState();

	class AAIController* AIController = nullptr;
	class APawn* AIPawn = nullptr;

	//UPROPERTY(EditAnywhere)
	//	FBlackboardKeySelector PointOfInterest;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ENPCState> State;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
