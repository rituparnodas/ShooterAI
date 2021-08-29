// Copyright DevDasTour 2021 All Right Reserved.


#include "AICGuard.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AICharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PerceptiveAI_Shooter/AI/AIPerceptionComp.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

AAICGuard::AAICGuard()
{
	AIPerceptioncomp = CreateDefaultSubobject<UAIPerceptionComp>(FName("AIPerceptionComp"));
	SetPerceptionComponent(*AIPerceptioncomp);
}

void AAICGuard::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetPerceptionComponent())
	{
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAICGuard::OnUpdatedPerception);		
	}

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

void AAICGuard::OnUpdatedPerception(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		AIPerceptioncomp->GetActorsPerception(Actor, PerceptionInfo);
		SensedActor = PerceptionInfo.Target;
		for (FAIStimulus AIStimulus : PerceptionInfo.LastSensedStimuli)
		{
			ActorSensedStimulus = AIStimulus;
			TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), ActorSensedStimulus);
			if (SenseClass == UAISense_Sight::StaticClass())
			{
				ProcessLastVisionStimuli();
			}
			else if (SenseClass == UAISense_Hearing::StaticClass())
			{

			}

		}
	}
}

void AAICGuard::ProcessLastVisionStimuli()
{
	if (SensedActor)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(SensedActor, UInterfaceAIHelper::StaticClass()))
		{

		}
	}
}