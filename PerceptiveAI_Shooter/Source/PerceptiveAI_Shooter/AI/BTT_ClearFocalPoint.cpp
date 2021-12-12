// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_ClearFocalPoint.h"
#include "PerceptiveAI_Shooter/AICGuard.h"

UBTT_ClearFocalPoint::UBTT_ClearFocalPoint()
{
	NodeName = "Clear Focal Point";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_ClearFocalPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();

	AAICGuard* AICGuard{ Cast<AAICGuard>(AIController) };
	if (!AICGuard) return EBTNodeResult::Failed;

	AICGuard->ClearFocus(EAIFocusPriority::Default);


	return EBTNodeResult::Succeeded;
}