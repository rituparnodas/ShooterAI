// Copyright DevDasTour 2021 All Right Reserved.

#include "PerceptiveAI_Shooter/AI/AIPerceptionComp.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

UAIPerceptionComp::UAIPerceptionComp()
{
	SetDominantSense(UAISense_Sight::StaticClass());

	bEditableWhenInherited = true;

	SetDominantSense(UAISenseConfig_Sight::StaticClass());
	bEditableWhenInherited = true;

	auto Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));
	auto Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(FName("Hearing"));
	auto Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(FName("Damage"));

	Sight->Implementation = UAISenseConfig_Sight::StaticClass();
	Sight->SightRadius = 1400.f;
	Sight->LoseSightRadius = 2000.f;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->SetMaxAge(6.f);
	
	Hearing->Implementation = UAISenseConfig_Sight::StaticClass();
	Hearing->HearingRange = 1000.f;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->SetMaxAge(3.f);
	
	Damage->Implementation = UAISenseConfig_Sight::StaticClass();
	Damage->SetMaxAge(3.f);
	
	SensesConfig.Add(Sight);
	SensesConfig.Add(Hearing);
	SensesConfig.Add(Damage);
}