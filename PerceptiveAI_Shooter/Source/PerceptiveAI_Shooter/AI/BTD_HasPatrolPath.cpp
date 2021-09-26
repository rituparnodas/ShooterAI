// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTD_HasPatrolPath.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"

UBTD_HasPatrolPath::UBTD_HasPatrolPath()
{
	NodeName = "HasPatrolPath";
}

bool UBTD_HasPatrolPath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	AAICharacterBase* AIPawn = Cast<AAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!AIPawn) return false;
	return UKismetSystemLibrary::IsValid(IInterfaceAIHelper::Execute_GetPatrolRoute(AIPawn));
}