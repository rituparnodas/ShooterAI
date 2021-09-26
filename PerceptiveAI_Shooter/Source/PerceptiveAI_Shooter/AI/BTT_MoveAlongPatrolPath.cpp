// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_MoveAlongPatrolPath.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "PerceptiveAI_Shooter/AICGuard.h"

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

	APatrolRoute* PatrolRoute = IInterfaceAIHelper::Execute_GetPatrolRoute(AIGuard);
	if (PatrolRoute)
	{
		PatrolRoute->GetNextPointAsWorldPosition();
		AAICGuard* AIGuardController = Cast<AAICGuard>(AIGuard->GetController());
		if (AIGuardController)
		{
			FAIMoveRequest Request;
			FPathFollowingRequestResult AIMoveToResult = AIGuardController->MoveTo(Request,);
		}
	}
		
	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}
