// Copyright DevDasTour 2021 All Right Reserved.


#include "AICGuard.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AICharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "PerceptiveAI_Shooter/FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "NavigationSystem.h"

AAICGuard::AAICGuard()
{
	AIPerceptioncomp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptionComp"));
	//SetPerceptionComponent(*AIPerceptioncomp);

	AIPerceptioncomp->SetDominantSense(UAISense_Sight::StaticClass());

	//AIPerceptioncomp->bEditableWhenInherited = true;

	/*auto Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));
	auto Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(FName("Hearing"));
	auto Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(FName("Damage"));

	Sight->Implementation = UAISense_Sight::StaticClass();
	Sight->SightRadius = 1400.f;
	Sight->LoseSightRadius = 2000.f;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->SetMaxAge(6.f);
	AIPerceptioncomp->ConfigureSense(*Sight);

	Hearing->Implementation = UAISense_Hearing::StaticClass();
	Hearing->HearingRange = 1000.f;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->SetMaxAge(3.f);
	AIPerceptioncomp->ConfigureSense(*Hearing);

	Damage->Implementation = UAISenseConfig_Damage::StaticClass();
	Damage->SetMaxAge(3.f);
	AIPerceptioncomp->ConfigureSense(*Damage);*/
}

void AAICGuard::BeginPlay()
{
	Super::BeginPlay();
	
	//if (GetPerceptionComponent())
	//{
		//GetPerceptionComponent()

	if (AIPerceptioncomp)
	{
		AIPerceptioncomp->OnPerceptionUpdated.AddDynamic(this, &AAICGuard::OnUpdatedPerception);
	}
	else
	{
		UE_LOG(LogTemp, Warning, L"AIPerceptioncomp Null");
	}
			
	//}

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
	Execute_NotifyChangeState(Cast<AAICharacterBase>(GetPawn()), ENPCState::Passive);
}

void AAICGuard::SetStateAsInvestigating(FVector MoveToLocation, FVector PointOfInterestLocation)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Investigating);
	GetBlackboardComponent()->SetValueAsVector(FName("MoveTo"), MoveToLocation);
	GetBlackboardComponent()->SetValueAsVector(FName("PointOfInterest"), PointOfInterestLocation);
	Execute_NotifyChangeState(Cast<AAICharacterBase>(GetPawn()), ENPCState::Investigating);
}

void AAICGuard::SetStateAsAttack(AActor* Target)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Attack);
	GetBlackboardComponent()->SetValueAsObject(FName("EnemyTarget"), Target);
	Execute_NotifyChangeState(Cast<AAICharacterBase>(GetPawn()), ENPCState::Attack);
}

void AAICGuard::SetStateAsSeeking(FVector Search)
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Seeking);
	GetBlackboardComponent()->SetValueAsVector(FName("MoveTo"), Search);
	Execute_NotifyChangeState(Cast<AAICharacterBase>(GetPawn()), ENPCState::Seeking);
}

void AAICGuard::SetStateAsDead()
{
	GetBlackboardComponent()->SetValueAsEnum("State", ENPCState::Dead);
	Execute_NotifyChangeState(Cast<AAICharacterBase>(GetPawn()),ENPCState::Dead);
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
				ProcessLastHearingStimuli();
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
			if (Execute_GetTeamID(Cast<AFP_FirstPersonCharacter>(SensedActor))) // If Seen Player Else Seen Friend
			{
				if (!Execute_GetIsDead(Cast<AFP_FirstPersonCharacter>(SensedActor)))
				{					
					if (ActorSensedStimulus.WasSuccessfullySensed())
					{
						SetStateAsAttack(SensedActor);
						UE_LOG(LogTemp, Warning, L"Attacking");
					}
					else
					{
						SetStateAsSeeking(ActorSensedStimulus.StimulusLocation);
						UE_LOG(LogTemp, Warning, L"Seeking");
					}
				}
				else
				{
					SetStateAsPassive();
					UE_LOG(LogTemp, Warning, L"SensedActor Dead");
				}
			}
			else // Friend
			{
				if (Execute_GetIsDead(Cast<AFP_FirstPersonCharacter>(SensedActor)))
				{
					SetStateAsSeeking(ActorSensedStimulus.StimulusLocation);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, L"SensedActor Null");
	}
}

void AAICGuard::ProcessLastHearingStimuli()
{
	if (ActorSensedStimulus.WasSuccessfullySensed())
	{
		FVector ProjectedLocation = UNavigationSystemV1::ProjectPointToNavigation(
			GetWorld(), 
			ActorSensedStimulus.StimulusLocation, 
			0, 
			0, 
			FVector(50.f, 50.f, 200.f)
		);

		if (ActorSensedStimulus.Tag == FName("GunShot"))
		{
			SetStateAsSeeking(ProjectedLocation);
		}
		else
		{
			SetStateAsInvestigating(ProjectedLocation, ActorSensedStimulus.StimulusLocation);
		}
	}
}