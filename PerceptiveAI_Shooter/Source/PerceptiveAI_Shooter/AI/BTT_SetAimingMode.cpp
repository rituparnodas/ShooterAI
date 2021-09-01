// Copyright DevDasTour 2021 All Right Reserved.

#include "PerceptiveAI_Shooter/AI/BTT_SetAimingMode.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"

UBTT_SetAimingMode::UBTT_SetAimingMode()
{
	NodeName = "Aiming";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_SetAimingMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(AIPawn);
	if(!AIGuard) return EBTNodeResult::Failed;
	IInterfaceAIHelper::Execute_ModifyAimingStance(AIGuard, IsAiming);

	UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}