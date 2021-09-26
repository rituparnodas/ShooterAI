// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTD_HasPatrolPath.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"

UBTD_HasPatrolPath::UBTD_HasPatrolPath()
{
	NodeName = "HasPatrolPath";
}

bool UBTD_HasPatrolPath::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	AAICharacterBase* AIPawn = Cast<AAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIPawn)
	{
		UE_LOG(LogTemp, Warning, L"ActorOwner Name : %s, Controller : %s ", *AIPawn->GetName(), *AIPawn->GetController()->GetName())
		//return false;
	}
	
	return true;
}