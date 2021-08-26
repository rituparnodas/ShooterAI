// Copyright DevDasTour 2021 All Right Reserved.


#include "AICGuard.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AICharacterBase.h"
#include "Perception/AIPerceptionComponent.h"

AAICGuard::AAICGuard()
{
	AIPerceptioncomp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptionComp"));
}

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
	return (ENPCState)GetBlackboardComponent()->GetValueAsEnum("State");
}

void AAICGuard::SetStateAsPassive()
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Passive);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Passive);
}

void AAICGuard::SetStateAsInvestigating(FVector MoveToLocation, FVector PointOfInterestLocation)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Investigating);
	GetBlackboardComponent()->SetValueAsVector(FName("MoveTo"), MoveToLocation);
	GetBlackboardComponent()->SetValueAsVector(FName("PointOfInterest"), PointOfInterestLocation);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Investigating);
}

void AAICGuard::SetStateAsAttack(AActor* Target)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Attack);
	GetBlackboardComponent()->SetValueAsObject(FName("EnemyTarget"), Target);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Attack);
}

void AAICGuard::SetStateAsSeeking(FVector Search)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Seeking);
	GetBlackboardComponent()->SetValueAsVector(FName("MoveTo"), Search);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Seeking);
}

void AAICGuard::SetStateAsDead()
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Dead);
	Cast<AAICharacterBase>(GetPawn())->NotifyChangeState(ENPCState::Dead);
}