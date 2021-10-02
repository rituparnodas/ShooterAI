// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_UpdateMovementSpeed.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(!BlackboardComp) return EBTNodeResult::Failed;

	uint8 BB_Enum = BlackboardComp->GetValueAsEnum(StateKey.SelectedKeyName);

	IInterfaceAIHelper::Execute_ModifyMovementSpeed(AIGuard, (ENPCState)BB_Enum);

	//UE_LOG(LogTemp, Warning, L"Executing");

	return EBTNodeResult::Succeeded;
}