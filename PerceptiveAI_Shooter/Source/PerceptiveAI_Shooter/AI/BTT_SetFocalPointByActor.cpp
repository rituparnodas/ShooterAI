// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_SetFocalPointByActor.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SetFocalPointByActor::UBTT_SetFocalPointByActor()
{
	NodeName = "Set Focal Point By Actor";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_SetFocalPointByActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	AAICGuard* AICGuard = Cast<AAICGuard>(AIController);
	if (!AICGuard) return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(EnemyTargetKey.SelectedKeyName));
	if (!TargetActor) return EBTNodeResult::Failed;
	AICGuard->SetFocus(TargetActor);

	return EBTNodeResult::Succeeded;
}