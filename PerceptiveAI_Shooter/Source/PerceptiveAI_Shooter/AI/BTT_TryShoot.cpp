// Copyright DevDasTour 2021 All Right Reserved.


#include "PerceptiveAI_Shooter/AI/BTT_TryShoot.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "PerceptiveAI_Shooter/AICGuard.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PerceptiveAI_Shooter/AICharacterBase.h"
#include "PerceptiveAI_Shooter/WeaponBase.h"

UBTT_TryShoot::UBTT_TryShoot()
{
	NodeName = " Try Shoot";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_TryShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	AAICGuard* AICGuard = Cast<AAICGuard>(AIController);
	if (!AICGuard) return EBTNodeResult::Failed;

	AAICharacterBase* AICharacter = Cast<AAICharacterBase>(AIPawn);
	if (!AICharacter) return EBTNodeResult::Failed;

	AWeaponBase* Weapon = IInterfaceAIHelper::Execute_GetWeapon(AICharacter);
	if (Weapon != nullptr)
	{
		IInterfaceAIHelper::Execute_TryShootEquipWeapon(AICharacter);
		Weapon->OnWeaponFired.RemoveDynamic(this, &UBTT_TryShoot::OnWeaponFired);
		Weapon->OnWeaponFired.AddDynamic(this, &UBTT_TryShoot::OnWeaponFired);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("Try Shoot Failed Due To Null Weapon"))
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

void UBTT_TryShoot::OnWeaponFired()
{

}