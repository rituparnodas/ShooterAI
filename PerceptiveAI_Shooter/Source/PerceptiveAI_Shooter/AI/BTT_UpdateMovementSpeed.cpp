// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_UpdateMovementSpeed.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTT_UpdateMovementSpeed::UBTT_UpdateMovementSpeed()
{
	NodeName = "ChangeMovementSpeed";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_UpdateMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	AAICharacterBase* AIGuard = Cast<AAICharacterBase>(AIPawn);
	if (!AIGuard) return EBTNodeResult::Failed;
	
	IInterfaceAIHelper::Execute_ModifyMovementSpeed(AIGuard, (ENPCState)UBTFunctionLibrary::GetBlackboardValueAsEnum(this, StateKey));

	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}