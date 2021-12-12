// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_SetFocalPointByLocation.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTT_SetFocalPointByLocation::UBTT_SetFocalPointByLocation()
{
	NodeName = "Set Focal Point By Location";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_SetFocalPointByLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();

	AAICGuard* AICGuard{ Cast<AAICGuard>(AIController) };
	if (!AICGuard) return EBTNodeResult::Failed;

	AICGuard->SetFocalPoint(UBTFunctionLibrary::GetBlackboardValueAsVector(this, PointOfInterest));

	return EBTNodeResult::Succeeded;
}