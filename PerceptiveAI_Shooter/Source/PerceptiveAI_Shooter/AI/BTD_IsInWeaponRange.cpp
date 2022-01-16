// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTD_IsInWeaponRange.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsInWeaponRange::UBTD_IsInWeaponRange()
{
	NodeName = "Is In Weapon Range";
}

bool UBTD_IsInWeaponRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	AAICharacterBase* AIPawn = Cast<AAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!AIPawn) return false;

	float WeaponRange = IInterfaceAIHelper::Execute_GetWeaponRange(AIPawn);

	UObject* TargetKeyObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
	if (!TargetKeyObject) return false;

	AActor* TargetKeyActor = Cast<AActor>(TargetKeyObject);
	if (!TargetKeyActor) return false;

	return !(AIPawn->GetDistanceTo(TargetKeyActor) >= WeaponRange);
}