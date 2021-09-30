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
		FVector NextPoint = PatrolRoute->GetNextPointAsWorldPosition();
		AAICGuard* AIGuardController = Cast<AAICGuard>(AIGuard->GetController());
		if (AIGuardController)
		{
			FAIMoveRequest MoveRequest;
			//MoveRequest.SetGoalActor(PatrolRoute);
			MoveRequest.SetGoalLocation(NextPoint);
			MoveRequest.SetAcceptanceRadius(15.f);
			MoveRequest.SetStopOnOverlap(false);
			FPathFollowingRequestResult AIMoveToResult = AIGuardController->MoveTo(MoveRequest);
			if (AIMoveToResult.Code == EPathFollowingRequestResult::RequestSuccessful)
			{
				PatrolRoute->IncrementPatrolPath(); // See 11.10 - 17:53
				UE_LOG(LogTemp, Warning, L"Request Successful");
			}
			else if (AIMoveToResult.Code == EPathFollowingRequestResult::Failed)
			{
				PatrolRoute->IncrementPatrolPath(); // See 11.10 - 17:53
				UE_LOG(LogTemp, Error, L"Request Failed");
			}
			else if (AIMoveToResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				PatrolRoute->IncrementPatrolPath(); // See 11.10 - 17:53
				UE_LOG(LogTemp, Warning, L"Request AlreadyAtGoal");
			}
		}
	}
		
	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}
