// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_ModifyState.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTT_ModifyState::UBTT_ModifyState()
{
	NodeName = "Modify State";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_ModifyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();

	AAICGuard* AICGuard{ Cast<AAICGuard>(AIController) };
	if (!AICGuard) return EBTNodeResult::Failed;

	AICGuard->SetStateAs(State);

	return EBTNodeResult::Succeeded;
}