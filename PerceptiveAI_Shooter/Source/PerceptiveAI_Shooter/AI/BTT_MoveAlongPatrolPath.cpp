// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_MoveAlongPatrolPath.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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

	PatrolRoute = IInterfaceAIHelper::Execute_GetPatrolRoute(AIGuard);
	if (PatrolRoute)
	{
		FVector NextPoint = PatrolRoute->GetNextPointAsWorldPosition();
		AAICGuard* AIGuardController = Cast<AAICGuard>(AIGuard->GetController());
		if (AIGuardController)
		{
			AIGuardController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_MoveAlongPatrolPath::OnMoveCompleted);
			AIGuardController->ReceiveMoveCompleted.AddDynamic(this, &UBTT_MoveAlongPatrolPath::OnMoveCompleted);
			UAIBlueprintHelperLibrary::CreateMoveToProxyObject(nullptr, AIGuard, NextPoint, nullptr, 15.f);			
		}
	}
		
	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}

void UBTT_MoveAlongPatrolPath::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	switch (Result)
	{
	case EPathFollowingResult::Success:
		UE_LOG(LogTemp, Warning, L"Success!!!");
		break;
	case EPathFollowingResult::Blocked:
		UE_LOG(LogTemp, Error, L"Blocked!!!");
		break;
	case EPathFollowingResult::OffPath:
		UE_LOG(LogTemp, Error, L"OffPath!!!");
		break;
	case EPathFollowingResult::Aborted:
		UE_LOG(LogTemp, Error, L"Aborted!!!");
		break;
	case EPathFollowingResult::Skipped_DEPRECATED:
		break;
	case EPathFollowingResult::Invalid:
		UE_LOG(LogTemp, Error, L"Invalid!!!");
		break;
	}

	PatrolRoute->IncrementPatrolPath();
}