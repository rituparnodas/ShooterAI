// Copyright DevDasTour 2021 All Right Reserved.


#include "AICGuard.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AICharacterBase.h"

void AAICGuard::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackBoardComponent = nullptr;
	UseBlackboard(BlackBoardData, BlackBoardComponent);

	RunBehaviorTree(AIBehavior);

	GetBlackboardComponent()->SetValueAsVector("SpawnLocation", GetPawn()->GetActorLocation());
}

void AAICGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ENPCState AAICGuard::GetNPCState()
{
	return (ENPCState)GetBlackboardComponent()->GetValueAsEnum(AIStateName);
}

void AAICGuard::SetStateAsPassive()
{
	GetBlackboardComponent()->SetValueAsEnum(AIStateName, ENPCState::Passive);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Passive);


	// Here Left Off
}