// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_RandomPointAroundTarget.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_RandomPointAroundTarget::UBTT_RandomPointAroundTarget()
{
	NodeName = "Random Point Around Target";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_RandomPointAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();

	AAICGuard* AICGuard{ Cast<AAICGuard>(AIController) };
	if (!AICGuard) return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(MoveToKey.SelectedKeyName);

	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
	FVector RandomPointInRadius = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), Origin, Radius);

	if (bIsAMoveLocation)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(MoveToKey.SelectedKeyName, RandomPointInRadius);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(POIKey.SelectedKeyName, Point);
	}

	return EBTNodeResult::Succeeded;
}