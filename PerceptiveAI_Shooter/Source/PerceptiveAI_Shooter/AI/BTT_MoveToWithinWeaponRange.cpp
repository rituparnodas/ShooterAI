// Copyright DevDasTour 2021 All Right Reserved.

#include "PerceptiveAI_Shooter/AI/BTT_MoveToWithinWeaponRange.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTT_MoveToWithinWeaponRange::UBTT_MoveToWithinWeaponRange()
{
	NodeName = "Move To Within Weapon Range";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_MoveToWithinWeaponRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(AIPawn);
	if (!AIGuard) return EBTNodeResult::Failed;

	AAICGuard* AICGuard{ Cast<AAICGuard>(AIController) };
	if (!AICGuard) return EBTNodeResult::Failed;

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(EnemyTargetKey.SelectedKeyName));



	AICGuard->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_MoveToWithinWeaponRange::OnMoveCompleted);
	AICGuard->ReceiveMoveCompleted.AddDynamic(this, &UBTT_MoveToWithinWeaponRange::OnMoveCompleted);
	UAIBlueprintHelperLibrary::CreateMoveToProxyObject(nullptr, AIGuard, FVector::ZeroVector, TargetActor, 150.f);

	return EBTNodeResult::Succeeded;
}

void UBTT_MoveToWithinWeaponRange::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
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
}