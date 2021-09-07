// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_MoveAlongPatrolPath.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTT_MoveAlongPatrolPath::UBTT_MoveAlongPatrolPath()
{
	NodeName = "MoveAlongPatrolPath";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_MoveAlongPatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(AIPawn);
	if (!AIGuard) return EBTNodeResult::Failed;

	

	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}
